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
typedef  scalar_t__ JAVA_BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GC_disable () ; 
 int /*<<< orphan*/  GC_enable () ; 

void org_xmlvm_runtime_FinalizerNotifier_preventGarbageCollection___boolean(JAVA_BOOLEAN n1)
{
    //XMLVM_BEGIN_NATIVE[org_xmlvm_runtime_FinalizerNotifier_preventGarbageCollection___boolean]
#ifndef XMLVM_NO_GC
    if (n1) {
        // Disable garbage collection.  Even GC_gcollect calls will be ineffective.
        GC_disable();
    } else {
        // Reenable garbage collection.  GC_disable() and GC_enable() calls
        // nest.  Garbage collection is enabled if the number of calls to both
        // functions is equal.
        GC_enable();
    }
#endif
    //XMLVM_END_NATIVE
}