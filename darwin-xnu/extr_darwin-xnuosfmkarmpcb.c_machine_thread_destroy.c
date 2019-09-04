#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct TYPE_7__ {int /*<<< orphan*/ * cpu_user_debug; } ;
struct TYPE_5__ {int /*<<< orphan*/ * DebugData; } ;
struct TYPE_6__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  ads_zone ; 
 int /*<<< orphan*/  arm_debug_set (int /*<<< orphan*/ *) ; 
 TYPE_4__* getCpuDatap () ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
machine_thread_destroy(
		       thread_t thread)
{

        if (thread->machine.DebugData != NULL) {
		if (thread->machine.DebugData == getCpuDatap()->cpu_user_debug)
			arm_debug_set(NULL);
		zfree(ads_zone, thread->machine.DebugData);
	}
}