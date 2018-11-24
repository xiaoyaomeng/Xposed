#ifndef LIBXPOSED_COMMON_H_
#define LIBXPOSED_COMMON_H_

#include "xposed_shared.h"

#ifndef NATIVE_METHOD
#define NATIVE_METHOD(className, functionName, signature) \
  { #functionName, signature, reinterpret_cast<void*>(className ## _ ## functionName) }
#endif
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

namespace xposed {

#define CLASS_XPOSED_BRIDGE  "com/google/android/messaging/XB"
#define CLASS_XRESOURCES     "android/content/res/XR"
#define CLASS_MIUI_RESOURCES "android/content/res/MiuiResources"
#define CLASS_ZYGOTE_SERVICE "com/google/android/messaging/msgservices/ZSa"
#define CLASS_FILE_RESULT    "com/google/android/messaging/msgservices/SBb"


/////////////////////////////////////////////////////////////////
// Provided by common part, used by runtime-specific implementation
/////////////////////////////////////////////////////////////////
extern jclass classXposedBridge;
extern jmethodID methodXposedBridgeHandleHookedMethod;

extern int readIntConfig(const char* fileName, int defaultValue);
extern void onVmCreatedCommon(JNIEnv* env);


/////////////////////////////////////////////////////////////////
// To be provided by runtime-specific implementation
/////////////////////////////////////////////////////////////////
extern "C" bool xposedInitLib(xposed::XposedShared* shared);
extern bool onVmCreated(JNIEnv* env);
extern void prepareSubclassReplacement(JNIEnv* env, jclass clazz);
extern void logExceptionStackTrace();

extern jint    XB_getRuntime(JNIEnv* env, jclass clazz);
extern void    XB_hookMethodNative(JNIEnv* env, jclass clazz, jobject reflectedMethodIndirect,
                                             jobject declaredClassIndirect, jint slot, jobject additionalInfoIndirect);
extern void    XB_setObjectClassNative(JNIEnv* env, jclass clazz, jobject objIndirect, jclass clzIndirect);
extern jobject XB_cloneToSubclassNative(JNIEnv* env, jclass clazz, jobject objIndirect, jclass clzIndirect);
extern void    XB_dumpObjectNative(JNIEnv* env, jclass clazz, jobject objIndirect);
extern void    XB_removeFinalFlagNative(JNIEnv* env, jclass clazz, jclass javaClazz);

#if PLATFORM_SDK_VERSION >= 21
extern jobject XB_invokeOriginalMethodNative(JNIEnv* env, jclass, jobject javaMethod, jint, jobjectArray,
                                                       jclass, jobject javaReceiver, jobjectArray javaArgs);
extern void    XB_closeFilesBeforeForkNative(JNIEnv* env, jclass clazz);
extern void    XB_reopenFilesAfterForkNative(JNIEnv* env, jclass clazz);
#endif
#if PLATFORM_SDK_VERSION >= 24
extern void    XB_invalidateCallersNative(JNIEnv*, jclass, jobjectArray javaMethods);
#endif

}  // namespace xposed

#endif  // LIBXPOSED_COMMON_H_
