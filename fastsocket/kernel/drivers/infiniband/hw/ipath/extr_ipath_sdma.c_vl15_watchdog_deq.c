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
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_vl15_timer; int /*<<< orphan*/  ipath_sdma_vl15_count; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void vl15_watchdog_deq(struct ipath_devdata *dd)
{
	/* ipath_sdma_lock must already be held */
	if (atomic_dec_return(&dd->ipath_sdma_vl15_count) != 0) {
		unsigned long interval = (HZ + 19) / 20;
		mod_timer(&dd->ipath_sdma_vl15_timer, jiffies + interval);
	} else {
		del_timer(&dd->ipath_sdma_vl15_timer);
	}
}