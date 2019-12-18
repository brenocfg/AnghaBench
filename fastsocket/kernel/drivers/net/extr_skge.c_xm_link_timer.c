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
typedef  int u16 ;
struct skge_port {int port; int /*<<< orphan*/  link_timer; struct skge_hw* hw; struct net_device* netdev; } ;
struct skge_hw {int /*<<< orphan*/  phy_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ LINK_HZ ; 
 int XM_GP_INP_ASS ; 
 int /*<<< orphan*/  XM_GP_PORT ; 
 int /*<<< orphan*/  XM_IMSK ; 
 int /*<<< orphan*/  XM_ISRC ; 
 int XM_IS_INP_ASS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ xm_check_link (struct net_device*) ; 
 int xm_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xm_link_timer(unsigned long arg)
{
	struct skge_port *skge = (struct skge_port *) arg;
	struct net_device *dev = skge->netdev;
 	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	int i;
	unsigned long flags;

	if (!netif_running(dev))
		return;

	spin_lock_irqsave(&hw->phy_lock, flags);

	/*
	 * Verify that the link by checking GPIO register three times.
	 * This pin has the signal from the link_sync pin connected to it.
	 */
	for (i = 0; i < 3; i++) {
		if (xm_read16(hw, port, XM_GP_PORT) & XM_GP_INP_ASS)
			goto link_down;
	}

        /* Re-enable interrupt to detect link down */
	if (xm_check_link(dev)) {
		u16 msk = xm_read16(hw, port, XM_IMSK);
		msk &= ~XM_IS_INP_ASS;
		xm_write16(hw, port, XM_IMSK, msk);
		xm_read16(hw, port, XM_ISRC);
	} else {
link_down:
		mod_timer(&skge->link_timer,
			  round_jiffies(jiffies + LINK_HZ));
	}
	spin_unlock_irqrestore(&hw->phy_lock, flags);
}