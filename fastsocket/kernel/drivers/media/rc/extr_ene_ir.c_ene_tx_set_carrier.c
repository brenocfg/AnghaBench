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
struct ene_device {int tx_period; int tx_duty_cycle; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENE_CIRCFG ; 
 int /*<<< orphan*/  ENE_CIRCFG_TX_CARR ; 
 int /*<<< orphan*/  ENE_CIRMOD_HPRD ; 
 int /*<<< orphan*/  ENE_CIRMOD_PRD ; 
 int ENE_CIRMOD_PRD_POL ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  ene_set_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ene_tx_set_carrier(struct ene_device *dev)
{
	u8 tx_puls_width;
	unsigned long flags;

	spin_lock_irqsave(&dev->hw_lock, flags);

	ene_set_clear_reg_mask(dev, ENE_CIRCFG,
		ENE_CIRCFG_TX_CARR, dev->tx_period > 0);

	if (!dev->tx_period)
		goto unlock;

	BUG_ON(dev->tx_duty_cycle >= 100 || dev->tx_duty_cycle <= 0);

	tx_puls_width = dev->tx_period / (100 / dev->tx_duty_cycle);

	if (!tx_puls_width)
		tx_puls_width = 1;

	dbg("TX: pulse distance = %d * 500 ns", dev->tx_period);
	dbg("TX: pulse width = %d * 500 ns", tx_puls_width);

	ene_write_reg(dev, ENE_CIRMOD_PRD, dev->tx_period | ENE_CIRMOD_PRD_POL);
	ene_write_reg(dev, ENE_CIRMOD_HPRD, tx_puls_width);
unlock:
	spin_unlock_irqrestore(&dev->hw_lock, flags);
}