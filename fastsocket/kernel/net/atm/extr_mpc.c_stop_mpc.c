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
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct mpoa_client {int /*<<< orphan*/ * old_ops; int /*<<< orphan*/  new_ops; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static void stop_mpc(struct mpoa_client *mpc)
{
	struct net_device *dev = mpc->dev;
	dprintk("mpoa: (%s) stop_mpc:", mpc->dev->name);

	/* Lets not nullify lec device's dev->hard_start_xmit */
	if (dev->netdev_ops != &mpc->new_ops) {
		dprintk(" mpc already stopped, not fatal\n");
		return;
	}
	dprintk("\n");

	dev->netdev_ops = mpc->old_ops;
	mpc->old_ops = NULL;

	/* close_shortcuts(mpc);    ??? FIXME */
}