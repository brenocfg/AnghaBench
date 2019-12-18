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
struct urb {struct mcs_cb* context; } ;
struct net_device {int dummy; } ;
struct mcs_cb {int /*<<< orphan*/  work; int /*<<< orphan*/  new_speed; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcs_send_irq(struct urb *urb)
{
	struct mcs_cb *mcs = urb->context;
	struct net_device *ndev = mcs->netdev;

	if (unlikely(mcs->new_speed))
		schedule_work(&mcs->work);
	else
		netif_wake_queue(ndev);
}