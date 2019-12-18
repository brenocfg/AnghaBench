#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {scalar_t__ c_switch; scalar_t__ kperf_c_switch; } ;

/* Variables and functions */

void
kperf_thread_set_dirty(thread_t thread, boolean_t dirty)
{
	if (dirty) {
		thread->kperf_c_switch = thread->c_switch - 1;
	} else {
		thread->kperf_c_switch = thread->c_switch;
	}
}