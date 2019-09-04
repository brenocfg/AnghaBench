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
 int /*<<< orphan*/  GC_should_invoke_finalizers () ; 

JAVA_BOOLEAN org_xmlvm_runtime_FinalizerNotifier_shouldInvokeFinalizers__()
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_FinalizerNotifier_shouldInvokeFinalizers__]
#ifndef XMLVM_NO_GC
    return GC_should_invoke_finalizers();
#else
    return 0;
#endif
    //XMLVM_END_NATIVE
}