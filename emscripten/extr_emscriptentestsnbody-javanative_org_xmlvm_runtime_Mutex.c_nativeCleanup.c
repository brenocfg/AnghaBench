#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nativeMutex_; } ;
struct TYPE_5__ {TYPE_1__ org_xmlvm_runtime_Mutex; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ org_xmlvm_runtime_Mutex ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  org_xmlvm_runtime_Mutex_addNativeMutexToFinalizerQueue___java_lang_Object (int /*<<< orphan*/ ) ; 

void nativeCleanup(void* me, void* client_data)
{
    JAVA_OBJECT m = ((org_xmlvm_runtime_Mutex*) me)->fields.org_xmlvm_runtime_Mutex.nativeMutex_;
    org_xmlvm_runtime_Mutex_addNativeMutexToFinalizerQueue___java_lang_Object(m);
}