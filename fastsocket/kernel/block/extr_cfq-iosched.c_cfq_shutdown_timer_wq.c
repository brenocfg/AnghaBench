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
struct cfq_data {int /*<<< orphan*/  unplug_work; int /*<<< orphan*/  idle_slice_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfq_shutdown_timer_wq(struct cfq_data *cfqd)
{
	del_timer_sync(&cfqd->idle_slice_timer);
	cancel_work_sync(&cfqd->unplug_work);
}