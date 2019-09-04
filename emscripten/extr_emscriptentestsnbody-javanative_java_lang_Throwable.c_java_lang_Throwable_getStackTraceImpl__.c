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

/* Variables and functions */
 int /*<<< orphan*/  XMLVM_UNIMPLEMENTED_NATIVE_METHOD () ; 
 int /*<<< orphan*/  printf (char*) ; 

JAVA_OBJECT java_lang_Throwable_getStackTraceImpl__(JAVA_OBJECT me)
{
    //XMLVM_BEGIN_NATIVE[java_lang_Throwable_getStackTraceImpl__]
#ifdef XMLVM_ENABLE_STACK_TRACES

    return ((java_lang_Throwable*) me)->fields.java_lang_Throwable.stackTrace_;

#else

// TODO throw RuntimeException with the following message instead of printf
    printf("Stack traces are not enabled natively! To enable stack traces, define XMLVM_ENABLE_STACK_TRACES. Keep in mind this will decrease performance!\n");
    XMLVM_UNIMPLEMENTED_NATIVE_METHOD();

#endif
    //XMLVM_END_NATIVE
}