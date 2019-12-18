#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union cpu_time_count {int dummy; } cpu_time_count ;
struct TYPE_3__ {int /*<<< orphan*/  expires; int /*<<< orphan*/ * task; } ;
struct TYPE_4__ {TYPE_1__ cpu; } ;
struct k_itimer {TYPE_2__ it; int /*<<< orphan*/  it_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_time_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union cpu_time_count) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_dead_task(struct k_itimer *timer, union cpu_time_count now)
{
	/*
	 * That's all for this thread or process.
	 * We leave our residual in expires to be reported.
	 */
	put_task_struct(timer->it.cpu.task);
	timer->it.cpu.task = NULL;
	timer->it.cpu.expires = cpu_time_sub(timer->it_clock,
					     timer->it.cpu.expires,
					     now);
}