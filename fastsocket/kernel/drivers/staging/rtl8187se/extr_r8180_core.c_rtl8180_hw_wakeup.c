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
struct r8180_priv {int /*<<< orphan*/  ps_lock; int /*<<< orphan*/  (* rf_wakeup ) (struct net_device*) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG4 ; 
 int CONFIG4_PWRMGT ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_hw_wakeup(struct net_device *dev)
{
	unsigned long flags;
	struct r8180_priv *priv = ieee80211_priv(dev);

	spin_lock_irqsave(&priv->ps_lock,flags);
	write_nic_byte(dev,CONFIG4,read_nic_byte(dev,CONFIG4)&~CONFIG4_PWRMGT);
	if (priv->rf_wakeup)
		priv->rf_wakeup(dev);
	spin_unlock_irqrestore(&priv->ps_lock,flags);
}