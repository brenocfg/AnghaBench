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
typedef  int /*<<< orphan*/  java_lang_Thread ;

/* Variables and functions */
 int /*<<< orphan*/  GC_unregister_my_thread () ; 
 int /*<<< orphan*/  java_lang_Thread_threadTerminating__ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 

void xmlvm_destroy(java_lang_Thread* mainThread)
{
#ifdef __EMSCRIPTEN__
	return; // Let the JS engine handle clean up
#endif

    java_lang_Thread_threadTerminating__(mainThread);

#ifdef XMLVM_ENABLE_STACK_TRACES
    JAVA_LONG nativeThreadId = (JAVA_LONG) pthread_self();
    destroyStackForExitingThread(nativeThreadId);
#endif

    // Unregister the current thread.  Only an explicitly registered
    // thread (i.e. for which GC_register_my_thread() returns GC_SUCCESS)
    // is allowed (and required) to call this function.  (As a special
    // exception, it is also allowed to once unregister the main thread.)
#ifndef XMLVM_NO_GC
    GC_unregister_my_thread();
#endif

    // Call pthread_exit(0) so that the main thread does not terminate until
    // the other threads have finished
    pthread_exit(0);
}