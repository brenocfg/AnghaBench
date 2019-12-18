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
struct net_device {int /*<<< orphan*/  trans_start; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct kaweth_device {int /*<<< orphan*/  tx_urb; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct kaweth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kaweth_tx_timeout(struct net_device *net)
{
	struct kaweth_device *kaweth = netdev_priv(net);

	dev_warn(&net->dev, "%s: Tx timed out. Resetting.\n", net->name);
	kaweth->stats.tx_errors++;
	net->trans_start = jiffies;

	usb_unlink_urb(kaweth->tx_urb);
}