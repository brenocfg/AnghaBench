#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * xmlvmExceptionEnv_; } ;
struct TYPE_8__ {TYPE_1__ java_lang_Thread; } ;
struct TYPE_9__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ java_lang_Thread ;
typedef  int /*<<< orphan*/  XMLVM_JMP_BUF ;
typedef  TYPE_3__* JAVA_OBJECT ;
typedef  int /*<<< orphan*/  JAVA_LONG ;

/* Variables and functions */
 scalar_t__ XMLVM_SETJMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_lang_Thread_run0___long (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  xmlvm_unhandled_exception () ; 

void threadRunner(JAVA_OBJECT me)
{
    java_lang_Thread* thiz = me;
    XMLVM_JMP_BUF xmlvm_exception_env;
    JAVA_LONG nativeThreadId = (JAVA_LONG) pthread_self();
    
#ifdef __OBJC__
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
#endif
#ifdef XMLVM_ENABLE_STACK_TRACES
    createStackForNewThread(nativeThreadId);
#endif

    if (XMLVM_SETJMP(xmlvm_exception_env)) {
        // Technically, XMLVM_UNWIND_EXCEPTION() should be called, but
        // exceptions will not be used anymore and XMLVM_ENTER_METHOD() wasn't
        // called (excessive), so a compilation error would occur

        xmlvm_unhandled_exception();
    } else {
        thiz->fields.java_lang_Thread.xmlvmExceptionEnv_ = &xmlvm_exception_env;
        java_lang_Thread_run0___long(thiz, nativeThreadId);
    }

#ifdef XMLVM_ENABLE_STACK_TRACES
    destroyStackForExitingThread(nativeThreadId);
#endif
#ifdef __OBJC__
    [pool release];
#endif
}