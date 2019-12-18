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
struct sgiseeq_regs {int dummy; } ;
struct sgiseeq_private {struct sgiseeq_regs* sregs; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int init_seeq (struct net_device*,struct sgiseeq_private*,struct sgiseeq_regs*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static inline int sgiseeq_reset(struct net_device *dev)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	struct sgiseeq_regs *sregs = sp->sregs;
	int err;

	err = init_seeq(dev, sp, sregs);
	if (err)
		return err;

	dev->trans_start = jiffies;
	netif_wake_queue(dev);

	return 0;
}