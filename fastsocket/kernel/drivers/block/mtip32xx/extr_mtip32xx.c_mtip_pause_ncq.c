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
struct mtip_port {void* ic_pause_timer; int /*<<< orphan*/  flags; TYPE_1__* dd; scalar_t__ mmio; struct host_to_dev_fis* rxfis; } ;
struct host_to_dev_fis {int command; int features; } ;
struct TYPE_2__ {int /*<<< orphan*/  dd_flag; } ;

/* Variables and functions */
 int ATA_CMD_DOWNLOAD_MICRO ; 
 int ATA_CMD_SEC_ERASE_PREP ; 
 int ATA_CMD_SEC_ERASE_UNIT ; 
 int /*<<< orphan*/  MTIP_DDF_SEC_LOCK_BIT ; 
 int /*<<< orphan*/  MTIP_PF_DM_ACTIVE_BIT ; 
 int /*<<< orphan*/  MTIP_PF_SE_ACTIVE_BIT ; 
 scalar_t__ PORT_TFDATA ; 
 int RX_FIS_D2H_REG ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mtip_restart_port (struct mtip_port*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mtip_pause_ncq(struct mtip_port *port,
				struct host_to_dev_fis *fis)
{
	struct host_to_dev_fis *reply;
	unsigned long task_file_data;

	reply = port->rxfis + RX_FIS_D2H_REG;
	task_file_data = readl(port->mmio+PORT_TFDATA);

	if (fis->command == ATA_CMD_SEC_ERASE_UNIT)
		clear_bit(MTIP_DDF_SEC_LOCK_BIT, &port->dd->dd_flag);

	if ((task_file_data & 1))
		return false;

	if (fis->command == ATA_CMD_SEC_ERASE_PREP) {
		set_bit(MTIP_PF_SE_ACTIVE_BIT, &port->flags);
		set_bit(MTIP_DDF_SEC_LOCK_BIT, &port->dd->dd_flag);
		port->ic_pause_timer = jiffies;
		return true;
	} else if ((fis->command == ATA_CMD_DOWNLOAD_MICRO) &&
					(fis->features == 0x03)) {
		set_bit(MTIP_PF_DM_ACTIVE_BIT, &port->flags);
		port->ic_pause_timer = jiffies;
		return true;
	} else if ((fis->command == ATA_CMD_SEC_ERASE_UNIT) ||
		((fis->command == 0xFC) &&
			(fis->features == 0x27 || fis->features == 0x72 ||
			 fis->features == 0x62 || fis->features == 0x26))) {
		/* Com reset after secure erase or lowlevel format */
		mtip_restart_port(port);
		return false;
	}

	return false;
}