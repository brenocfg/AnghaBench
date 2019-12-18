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
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_vl15_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_cancel_sends (struct ipath_devdata*,int) ; 
 int /*<<< orphan*/  ipath_dbg (char*) ; 
 int /*<<< orphan*/  ipath_hol_down (struct ipath_devdata*) ; 

__attribute__((used)) static void vl15_watchdog_timeout(unsigned long opaque)
{
	struct ipath_devdata *dd = (struct ipath_devdata *)opaque;

	if (atomic_read(&dd->ipath_sdma_vl15_count) != 0) {
		ipath_dbg("vl15 watchdog timeout - clearing\n");
		ipath_cancel_sends(dd, 1);
		ipath_hol_down(dd);
	} else {
		ipath_dbg("vl15 watchdog timeout - "
			  "condition already cleared\n");
	}
}