#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ expires; } ;
struct ipath_devdata {TYPE_1__ ipath_sdma_vl15_timer; int /*<<< orphan*/  ipath_sdma_vl15_count; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void vl15_watchdog_enq(struct ipath_devdata *dd)
{
	/* ipath_sdma_lock must already be held */
	if (atomic_inc_return(&dd->ipath_sdma_vl15_count) == 1) {
		unsigned long interval = (HZ + 19) / 20;
		dd->ipath_sdma_vl15_timer.expires = jiffies + interval;
		add_timer(&dd->ipath_sdma_vl15_timer);
	}
}