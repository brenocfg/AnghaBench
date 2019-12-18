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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPACPI_RFK_WWAN_SW_ID ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpacpi_destroy_rfkill (int /*<<< orphan*/ ) ; 
 TYPE_2__* tpacpi_pdev ; 
 int /*<<< orphan*/  wan_attr_group ; 
 int /*<<< orphan*/  wan_shutdown () ; 

__attribute__((used)) static void wan_exit(void)
{
	sysfs_remove_group(&tpacpi_pdev->dev.kobj,
		&wan_attr_group);

	tpacpi_destroy_rfkill(TPACPI_RFK_WWAN_SW_ID);

	wan_shutdown();
}