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
typedef  int /*<<< orphan*/  JAVA_BOOLEAN ;

/* Variables and functions */

JAVA_BOOLEAN java_lang_Thread_stackTracesEnabled__()
{
    //XMLVM_BEGIN_NATIVE[java_lang_Thread_stackTracesEnabled__]
#ifdef XMLVM_ENABLE_STACK_TRACES
    return 1;
#else
    return 0;
#endif
    //XMLVM_END_NATIVE
}