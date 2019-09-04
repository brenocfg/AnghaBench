#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void xmlvm_init_native_java_lang_Thread()
{
    //XMLVM_BEGIN_NATIVE_IMPLEMENTATION_INIT
    //XMLVM_END_NATIVE_IMPLEMENTATION_INIT
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_checkAccess__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_checkAccess__] = 
        (VTABLE_PTR) java_lang_Thread_checkAccess__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_countStackFrames__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_countStackFrames__] = 
        (VTABLE_PTR) java_lang_Thread_countStackFrames__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_destroy__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_destroy__] = 
        (VTABLE_PTR) java_lang_Thread_destroy__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_getContextClassLoader__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_getContextClassLoader__] = 
        (VTABLE_PTR) java_lang_Thread_getContextClassLoader__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_getStackTrace__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_getStackTrace__] = 
        (VTABLE_PTR) java_lang_Thread_getStackTrace__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_getUncaughtExceptionHandler__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_getUncaughtExceptionHandler__] = 
        (VTABLE_PTR) java_lang_Thread_getUncaughtExceptionHandler__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_join___long_int
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_join___long_int] = 
        (VTABLE_PTR) java_lang_Thread_join___long_int;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_resume__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_resume__] = 
        (VTABLE_PTR) java_lang_Thread_resume__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_setContextClassLoader___java_lang_ClassLoader
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_setContextClassLoader___java_lang_ClassLoader] = 
        (VTABLE_PTR) java_lang_Thread_setContextClassLoader___java_lang_ClassLoader;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_setPriority___int
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_setPriority___int] = 
        (VTABLE_PTR) java_lang_Thread_setPriority___int;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_setUncaughtExceptionHandler___java_lang_Thread_UncaughtExceptionHandler
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_setUncaughtExceptionHandler___java_lang_Thread_UncaughtExceptionHandler] = 
        (VTABLE_PTR) java_lang_Thread_setUncaughtExceptionHandler___java_lang_Thread_UncaughtExceptionHandler;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_start0__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_start0__] = 
        (VTABLE_PTR) java_lang_Thread_start0__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_stop__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_stop__] = 
        (VTABLE_PTR) java_lang_Thread_stop__;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_stop___java_lang_Throwable
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_stop___java_lang_Throwable] = 
        (VTABLE_PTR) java_lang_Thread_stop___java_lang_Throwable;
#endif
#ifdef XMLVM_VTABLE_IDX_java_lang_Thread_suspend__
    __TIB_java_lang_Thread.vtable[XMLVM_VTABLE_IDX_java_lang_Thread_suspend__] = 
        (VTABLE_PTR) java_lang_Thread_suspend__;
#endif
}