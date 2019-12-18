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
struct TYPE_2__ {scalar_t__ expires; } ;
struct ax_device {TYPE_1__ mii_timer; scalar_t__ running; int /*<<< orphan*/  mii_lock; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_msg_link (struct ax_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 

__attribute__((used)) static void ax_mii_expiry(unsigned long data)
{
	struct net_device *dev = (struct net_device *)data;
	struct ax_device  *ax = to_ax_dev(dev);
	unsigned long flags;

	spin_lock_irqsave(&ax->mii_lock, flags);
	mii_check_media(&ax->mii, netif_msg_link(ax), 0);
	spin_unlock_irqrestore(&ax->mii_lock, flags);

	if (ax->running) {
		ax->mii_timer.expires = jiffies + HZ*2;
		add_timer(&ax->mii_timer);
	}
}