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
struct ethtool_eeprom {int offset; int len; scalar_t__ magic; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 scalar_t__ CP_EEPROM_MAGIC ; 
 int EINVAL ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int read_eeprom (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_eeprom (int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static int cp_set_eeprom(struct net_device *dev,
			 struct ethtool_eeprom *eeprom, u8 *data)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned int addr_len;
	u16 val;
	u32 offset = eeprom->offset >> 1;
	u32 len = eeprom->len;
	u32 i = 0;

	if (eeprom->magic != CP_EEPROM_MAGIC)
		return -EINVAL;

	spin_lock_irq(&cp->lock);

	addr_len = read_eeprom(cp->regs, 0, 8) == 0x8129 ? 8 : 6;

	if (eeprom->offset & 1) {
		val = read_eeprom(cp->regs, offset, addr_len) & 0xff;
		val |= (u16)data[i++] << 8;
		write_eeprom(cp->regs, offset, val, addr_len);
		offset++;
	}

	while (i < len - 1) {
		val = (u16)data[i++];
		val |= (u16)data[i++] << 8;
		write_eeprom(cp->regs, offset, val, addr_len);
		offset++;
	}

	if (i < len) {
		val = read_eeprom(cp->regs, offset, addr_len) & 0xff00;
		val |= (u16)data[i];
		write_eeprom(cp->regs, offset, val, addr_len);
	}

	spin_unlock_irq(&cp->lock);
	return 0;
}