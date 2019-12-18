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
struct omap_hwmod_ocp_if {int user; } ;
struct omap_hwmod {int slaves_cnt; int /*<<< orphan*/  name; struct omap_hwmod_ocp_if** slaves; } ;

/* Variables and functions */
 int EINVAL ; 
 int OCP_USER_MPU ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int _find_mpu_port_index(struct omap_hwmod *oh)
{
	struct omap_hwmod_ocp_if *os;
	int i;
	int found = 0;

	if (!oh || oh->slaves_cnt == 0)
		return -EINVAL;

	for (i = 0, os = *oh->slaves; i < oh->slaves_cnt; i++, os++) {
		if (os->user & OCP_USER_MPU) {
			found = 1;
			break;
		}
	}

	if (found)
		pr_debug("omap_hwmod: %s: MPU OCP slave port ID  %d\n",
			 oh->name, i);
	else
		pr_debug("omap_hwmod: %s: no MPU OCP slave port found\n",
			 oh->name);

	return (found) ? i : -EINVAL;
}