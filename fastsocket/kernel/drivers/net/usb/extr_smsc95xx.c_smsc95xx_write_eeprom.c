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
typedef  int u8 ;
typedef  int u32 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_ADDR_ ; 
 int E2P_CMD_BUSY_ ; 
 int E2P_CMD_EWEN_ ; 
 int E2P_CMD_WRITE_ ; 
 int /*<<< orphan*/  E2P_DATA ; 
 int smsc95xx_eeprom_confirm_not_busy (struct usbnet*) ; 
 int smsc95xx_wait_eeprom (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc95xx_write_eeprom(struct usbnet *dev, u32 offset, u32 length,
				 u8 *data)
{
	u32 val;
	int i, ret;

	BUG_ON(!dev);
	BUG_ON(!data);

	ret = smsc95xx_eeprom_confirm_not_busy(dev);
	if (ret)
		return ret;

	/* Issue write/erase enable command */
	val = E2P_CMD_BUSY_ | E2P_CMD_EWEN_;
	smsc95xx_write_reg(dev, E2P_CMD, val);

	ret = smsc95xx_wait_eeprom(dev);
	if (ret < 0)
		return ret;

	for (i = 0; i < length; i++) {

		/* Fill data register */
		val = data[i];
		smsc95xx_write_reg(dev, E2P_DATA, val);

		/* Send "write" command */
		val = E2P_CMD_BUSY_ | E2P_CMD_WRITE_ | (offset & E2P_CMD_ADDR_);
		smsc95xx_write_reg(dev, E2P_CMD, val);

		ret = smsc95xx_wait_eeprom(dev);
		if (ret < 0)
			return ret;

		offset++;
	}

	return 0;
}