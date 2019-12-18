#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ elp_device ;

/* Variables and functions */
 int HCR_VAL (struct net_device*) ; 
 int HSF_PCB_MASK ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb_control (int,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void set_hsf(struct net_device *dev, int hsf)
{
	elp_device *adapter = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&adapter->lock, flags);
	outb_control((HCR_VAL(dev) & ~HSF_PCB_MASK) | hsf, dev);
	spin_unlock_irqrestore(&adapter->lock, flags);
}