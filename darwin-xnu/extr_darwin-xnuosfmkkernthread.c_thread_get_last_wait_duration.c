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
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {scalar_t__ last_run_time; scalar_t__ last_made_runnable_time; } ;

/* Variables and functions */

uint64_t
thread_get_last_wait_duration(thread_t thread)
{
	return thread->last_made_runnable_time - thread->last_run_time;
}