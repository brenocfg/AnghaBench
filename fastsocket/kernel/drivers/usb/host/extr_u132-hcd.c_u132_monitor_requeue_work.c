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
struct u132 {int /*<<< orphan*/  kref; int /*<<< orphan*/  monitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  u132_hcd_delete ; 
 int /*<<< orphan*/  workqueue ; 

__attribute__((used)) static void u132_monitor_requeue_work(struct u132 *u132, unsigned int delta)
{
	if (!queue_delayed_work(workqueue, &u132->monitor, delta))
		kref_put(&u132->kref, u132_hcd_delete);
}