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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * clr_addr; int /*<<< orphan*/ * set_addr; } ;

/* Variables and functions */
 TYPE_1__ cpustate ; 
 int /*<<< orphan*/  cpustate_dev ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdpu_cpustate_remove(struct platform_device *pdev)
{
	cpustate.set_addr = NULL;
	cpustate.clr_addr = NULL;

	remove_proc_entry("sky_cpustate", NULL);
	misc_deregister(&cpustate_dev);

	return 0;
}