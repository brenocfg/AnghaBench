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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  cpcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CpCmd ; 
 int /*<<< orphan*/  RxChkSum ; 
 int /*<<< orphan*/  cpw16_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cp_set_rx_csum(struct net_device *dev, u32 data)
{
	struct cp_private *cp = netdev_priv(dev);
	u16 cmd = cp->cpcmd, newcmd;

	newcmd = cmd;

	if (data)
		newcmd |= RxChkSum;
	else
		newcmd &= ~RxChkSum;

	if (newcmd != cmd) {
		unsigned long flags;

		spin_lock_irqsave(&cp->lock, flags);
		cp->cpcmd = newcmd;
		cpw16_f(CpCmd, newcmd);
		spin_unlock_irqrestore(&cp->lock, flags);
	}

	return 0;
}