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
struct TYPE_2__ {int /*<<< orphan*/  deleted; } ;
struct ipoib_dev_priv {TYPE_1__ ntbl; int /*<<< orphan*/  neigh_reap_task; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_NEIGH_TBL_FLUSH ; 
 int /*<<< orphan*/  IPOIB_STOP_NEIGH_GC ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_flush_neighs (struct ipoib_dev_priv*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_neigh_hash_uninit(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	int stopped;

	ipoib_dbg(priv, "ipoib_neigh_hash_uninit\n");
	init_completion(&priv->ntbl.deleted);
	set_bit(IPOIB_NEIGH_TBL_FLUSH, &priv->flags);

	/* Stop GC if called at init fail need to cancel work */
	stopped = test_and_set_bit(IPOIB_STOP_NEIGH_GC, &priv->flags);
	if (!stopped)
		cancel_delayed_work(&priv->neigh_reap_task);

	ipoib_flush_neighs(priv);

	wait_for_completion(&priv->ntbl.deleted);
}