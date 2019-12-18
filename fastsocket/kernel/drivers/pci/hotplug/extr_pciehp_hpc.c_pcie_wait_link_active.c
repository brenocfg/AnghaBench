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
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_link_active (struct controller*) ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void pcie_wait_link_active(struct controller *ctrl)
{
	int timeout = 1000;

	if (check_link_active(ctrl))
		return;
	while (timeout > 0) {
		msleep(10);
		timeout -= 10;
		if (check_link_active(ctrl))
			return;
	}
	ctrl_dbg(ctrl, "Data Link Layer Link Active not set in 1000 msec\n");
}