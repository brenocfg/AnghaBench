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
struct r8180_priv {int irq_enabled; int /*<<< orphan*/  irq_mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTA_MASK ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8180_irq_enable(struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	priv->irq_enabled = 1;
	write_nic_word(dev,INTA_MASK, priv->irq_mask);
}