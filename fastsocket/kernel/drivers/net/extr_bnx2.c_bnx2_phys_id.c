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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_EMAC_LED ; 
 int BNX2_EMAC_LED_1000MB_OVERRIDE ; 
 int BNX2_EMAC_LED_100MB_OVERRIDE ; 
 int BNX2_EMAC_LED_10MB_OVERRIDE ; 
 int BNX2_EMAC_LED_OVERRIDE ; 
 int BNX2_EMAC_LED_TRAFFIC ; 
 int BNX2_EMAC_LED_TRAFFIC_OVERRIDE ; 
 int /*<<< orphan*/  BNX2_MISC_CFG ; 
 int BNX2_MISC_CFG_LEDMODE_MAC ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  bnx2_set_power_state (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_phys_id(struct net_device *dev, u32 data)
{
	struct bnx2 *bp = netdev_priv(dev);
	int i;
	u32 save;

	bnx2_set_power_state(bp, PCI_D0);

	if (data == 0)
		data = 2;

	save = BNX2_RD(bp, BNX2_MISC_CFG);
	BNX2_WR(bp, BNX2_MISC_CFG, BNX2_MISC_CFG_LEDMODE_MAC);

	for (i = 0; i < (data * 2); i++) {
		if ((i % 2) == 0) {
			BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE);
		}
		else {
			BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE |
				BNX2_EMAC_LED_1000MB_OVERRIDE |
				BNX2_EMAC_LED_100MB_OVERRIDE |
				BNX2_EMAC_LED_10MB_OVERRIDE |
				BNX2_EMAC_LED_TRAFFIC_OVERRIDE |
				BNX2_EMAC_LED_TRAFFIC);
		}
		msleep_interruptible(500);
		if (signal_pending(current))
			break;
	}
	BNX2_WR(bp, BNX2_EMAC_LED, 0);
	BNX2_WR(bp, BNX2_MISC_CFG, save);

	if (!netif_running(dev))
		bnx2_set_power_state(bp, PCI_D3hot);

	return 0;
}