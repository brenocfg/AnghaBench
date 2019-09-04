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
typedef  int /*<<< orphan*/  JAVA_OBJECT ;
typedef  int JAVA_BOOLEAN ;

/* Variables and functions */
 scalar_t__ java_lang_Thread_getCurrentThreadNativeId__ () ; 
 scalar_t__ java_lang_Thread_getNativeThreadId__ (int /*<<< orphan*/ ) ; 

JAVA_BOOLEAN org_xmlvm_runtime_FinalizerNotifier_currentThreadIsFinalizerThread___java_lang_Thread(JAVA_OBJECT n1)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_FinalizerNotifier_currentThreadIsFinalizerThread___java_lang_Thread]

    // Determine if the current thread is the finalizer thread (the 1st
    // parameter).

    // This method is native since any methods added to proxy classes are not
    // visible to this class, such as Thread.getCurrentThreadNativeId().

    // return Thread.getCurrentThreadNativeId() == finalizerThread.getNativeThreadId();
    return java_lang_Thread_getCurrentThreadNativeId__() == java_lang_Thread_getNativeThreadId__(n1);

    //XMLVM_END_NATIVE
}