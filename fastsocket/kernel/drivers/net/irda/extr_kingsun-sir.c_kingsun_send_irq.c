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
struct urb {scalar_t__ status; struct kingsun_cb* context; } ;
struct net_device {int dummy; } ;
struct kingsun_cb {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void kingsun_send_irq(struct urb *urb)
{
	struct kingsun_cb *kingsun = urb->context;
	struct net_device *netdev = kingsun->netdev;

	/* in process of stopping, just drop data */
	if (!netif_running(kingsun->netdev)) {
		err("kingsun_send_irq: Network not running!");
		return;
	}

	/* unlink, shutdown, unplug, other nasties */
	if (urb->status != 0) {
		err("kingsun_send_irq: urb asynchronously failed - %d",
		    urb->status);
	}
	netif_wake_queue(netdev);
}