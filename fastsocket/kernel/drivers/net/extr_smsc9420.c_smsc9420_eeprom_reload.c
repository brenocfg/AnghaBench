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
struct smsc9420_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_EPC_BUSY_ ; 
 int E2P_CMD_EPC_CMD_RELOAD_ ; 
 int EIO ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  smsc_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int smsc9420_eeprom_reload(struct smsc9420_pdata *pd)
{
	int timeout = 100000;

	BUG_ON(!pd);

	if (smsc9420_reg_read(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_) {
		smsc_dbg(DRV, "smsc9420_eeprom_reload: Eeprom busy");
		return -EIO;
	}

	smsc9420_reg_write(pd, E2P_CMD,
		(E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_RELOAD_));

	do {
		udelay(10);
		if (!(smsc9420_reg_read(pd, E2P_CMD) & E2P_CMD_EPC_BUSY_))
			return 0;
	} while (timeout--);

	smsc_warn(DRV, "smsc9420_eeprom_reload: Eeprom timed out");
	return -EIO;
}