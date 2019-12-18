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
struct net_device {int dummy; } ;
struct TYPE_2__ {unsigned int phy_irq_pin; } ;
struct at91_private {scalar_t__ phy_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  check_timer; TYPE_1__ board_data; } ;

/* Variables and functions */
 scalar_t__ MII_BCM5221_ID ; 
 int /*<<< orphan*/  MII_BCMINTR_REG ; 
 scalar_t__ MII_DM9161A_ID ; 
 scalar_t__ MII_DM9161_ID ; 
 scalar_t__ MII_DP83848_ID ; 
 int /*<<< orphan*/  MII_DPMICR_REG ; 
 int /*<<< orphan*/  MII_DPMISR_REG ; 
 int /*<<< orphan*/  MII_DSINTR_REG ; 
 int /*<<< orphan*/  MII_ISINTE_REG ; 
 scalar_t__ MII_KS8721_ID ; 
 scalar_t__ MII_LXT971A_ID ; 
 int /*<<< orphan*/  MII_T78Q21INT_REG ; 
 scalar_t__ MII_T78Q21x3_ID ; 
 int /*<<< orphan*/  MII_TPISTATUS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_mdi () ; 
 int /*<<< orphan*/  enable_mdi () ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct net_device*) ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void disable_phyirq(struct net_device *dev)
{
	struct at91_private *lp = netdev_priv(dev);
	unsigned int dsintr;
	unsigned int irq_number;

	irq_number = lp->board_data.phy_irq_pin;
	if (!irq_number) {
		del_timer_sync(&lp->check_timer);
		return;
	}

	spin_lock_irq(&lp->lock);
	enable_mdi();

	if ((lp->phy_type == MII_DM9161_ID) || (lp->phy_type == MII_DM9161A_ID)) {	/* for Davicom PHY */
		read_phy(lp->phy_address, MII_DSINTR_REG, &dsintr);
		dsintr = dsintr | 0xf00;			/* set bits 8..11 */
		write_phy(lp->phy_address, MII_DSINTR_REG, dsintr);
	}
	else if (lp->phy_type == MII_LXT971A_ID) {	/* for Intel PHY */
		read_phy(lp->phy_address, MII_ISINTE_REG, &dsintr);
		dsintr = dsintr & ~0xf2;			/* clear bits 1, 4..7 */
		write_phy(lp->phy_address, MII_ISINTE_REG, dsintr);
	}
	else if (lp->phy_type == MII_BCM5221_ID) {	/* for Broadcom PHY */
		read_phy(lp->phy_address, MII_BCMINTR_REG, &dsintr);
		dsintr = ~(1 << 14);
		write_phy(lp->phy_address, MII_BCMINTR_REG, dsintr);
	}
	else if (lp->phy_type == MII_KS8721_ID) {	/* for Micrel PHY */
		read_phy(lp->phy_address, MII_TPISTATUS, &dsintr);
		dsintr = ~((1 << 10) | (1 << 8));
		write_phy(lp->phy_address, MII_TPISTATUS, dsintr);
	}
	else if (lp->phy_type == MII_T78Q21x3_ID) {	/* for Teridian PHY */
		read_phy(lp->phy_address, MII_T78Q21INT_REG, &dsintr);
		dsintr = dsintr & ~0x500;			/* clear bits 8, 10 */
		write_phy(lp->phy_address, MII_T78Q21INT_REG, dsintr);
	}
	else if (lp->phy_type == MII_DP83848_ID) {	/* National Semiconductor DP83848 PHY */
		read_phy(lp->phy_address, MII_DPMICR_REG, &dsintr);
		dsintr = dsintr & ~0x3;				/* clear bits 0, 1 */
		write_phy(lp->phy_address, MII_DPMICR_REG, dsintr);
		read_phy(lp->phy_address, MII_DPMISR_REG, &dsintr);
		dsintr = dsintr & ~0x3c;			/* clear bits 2..5 */
		write_phy(lp->phy_address, MII_DPMISR_REG, dsintr);
	}

	disable_mdi();
	spin_unlock_irq(&lp->lock);

	free_irq(irq_number, dev);			/* Free interrupt handler */
}