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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int offset; int len; int /*<<< orphan*/  magic; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_EEPROM_MAGIC ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int read_eeprom (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cp_get_eeprom(struct net_device *dev,
			 struct ethtool_eeprom *eeprom, u8 *data)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned int addr_len;
	u16 val;
	u32 offset = eeprom->offset >> 1;
	u32 len = eeprom->len;
	u32 i = 0;

	eeprom->magic = CP_EEPROM_MAGIC;

	spin_lock_irq(&cp->lock);

	addr_len = read_eeprom(cp->regs, 0, 8) == 0x8129 ? 8 : 6;

	if (eeprom->offset & 1) {
		val = read_eeprom(cp->regs, offset, addr_len);
		data[i++] = (u8)(val >> 8);
		offset++;
	}

	while (i < len - 1) {
		val = read_eeprom(cp->regs, offset, addr_len);
		data[i++] = (u8)val;
		data[i++] = (u8)(val >> 8);
		offset++;
	}

	if (i < len) {
		val = read_eeprom(cp->regs, offset, addr_len);
		data[i] = (u8)val;
	}

	spin_unlock_irq(&cp->lock);
	return 0;
}