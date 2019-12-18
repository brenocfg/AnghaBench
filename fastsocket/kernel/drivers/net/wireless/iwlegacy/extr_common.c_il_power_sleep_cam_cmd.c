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
struct TYPE_2__ {scalar_t__ pci_pm; } ;
struct il_priv {TYPE_1__ power_data; } ;
struct il_powertable_cmd {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_POWER (char*) ; 
 int /*<<< orphan*/  IL_POWER_PCI_PM_MSK ; 
 int /*<<< orphan*/  memset (struct il_powertable_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
il_power_sleep_cam_cmd(struct il_priv *il, struct il_powertable_cmd *cmd)
{
	memset(cmd, 0, sizeof(*cmd));

	if (il->power_data.pci_pm)
		cmd->flags |= IL_POWER_PCI_PM_MSK;

	D_POWER("Sleep command for CAM\n");
}