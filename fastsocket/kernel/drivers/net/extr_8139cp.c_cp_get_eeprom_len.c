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
struct net_device {int dummy; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 struct cp_private* netdev_priv (struct net_device*) ; 
 int read_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cp_get_eeprom_len(struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	int size;

	spin_lock_irq(&cp->lock);
	size = read_eeprom(cp->regs, 0, 8) == 0x8129 ? 256 : 128;
	spin_unlock_irq(&cp->lock);

	return size;
}