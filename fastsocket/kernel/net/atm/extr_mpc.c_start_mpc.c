#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_2__* netdev_ops; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndo_start_xmit; } ;
struct mpoa_client {TYPE_2__ new_ops; TYPE_2__* old_ops; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_send_packet ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_mpc(struct mpoa_client *mpc, struct net_device *dev)
{

	dprintk("mpoa: (%s) start_mpc:\n", mpc->dev->name);
	if (!dev->netdev_ops)
		printk("mpoa: (%s) start_mpc  not starting\n", dev->name);
	else {
		mpc->old_ops = dev->netdev_ops;
		mpc->new_ops = *mpc->old_ops;
		mpc->new_ops.ndo_start_xmit = mpc_send_packet;
		dev->netdev_ops = &mpc->new_ops;
	}
}