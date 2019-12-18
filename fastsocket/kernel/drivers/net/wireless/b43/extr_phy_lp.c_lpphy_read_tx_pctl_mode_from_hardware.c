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
typedef  int u16 ;
struct TYPE_2__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_lp {int /*<<< orphan*/  txpctl_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_TXPCTL_HW ; 
 int /*<<< orphan*/  B43_LPPHY_TXPCTL_OFF ; 
 int /*<<< orphan*/  B43_LPPHY_TXPCTL_SW ; 
 int /*<<< orphan*/  B43_LPPHY_TXPCTL_UNKNOWN ; 
 int /*<<< orphan*/  B43_LPPHY_TX_PWR_CTL_CMD ; 
 int B43_LPPHY_TX_PWR_CTL_CMD_MODE ; 
#define  B43_LPPHY_TX_PWR_CTL_CMD_MODE_HW 130 
#define  B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF 129 
#define  B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpphy_read_tx_pctl_mode_from_hardware(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	u16 ctl;

	ctl = b43_phy_read(dev, B43_LPPHY_TX_PWR_CTL_CMD);
	switch (ctl & B43_LPPHY_TX_PWR_CTL_CMD_MODE) {
	case B43_LPPHY_TX_PWR_CTL_CMD_MODE_OFF:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_OFF;
		break;
	case B43_LPPHY_TX_PWR_CTL_CMD_MODE_SW:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_SW;
		break;
	case B43_LPPHY_TX_PWR_CTL_CMD_MODE_HW:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_HW;
		break;
	default:
		lpphy->txpctl_mode = B43_LPPHY_TXPCTL_UNKNOWN;
		B43_WARN_ON(1);
		break;
	}
}