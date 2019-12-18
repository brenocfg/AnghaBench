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
struct ipoib_path {int dummy; } ;
struct ipoib_neigh {struct ipoib_cm_tx* cm; } ;
struct TYPE_2__ {int /*<<< orphan*/  start_task; int /*<<< orphan*/  start_list; } ;
struct ipoib_dev_priv {TYPE_1__ cm; } ;
struct ipoib_cm_tx {int /*<<< orphan*/  flags; int /*<<< orphan*/  list; struct net_device* dev; struct ipoib_path* path; struct ipoib_neigh* neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 struct ipoib_cm_tx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct ipoib_cm_tx *ipoib_cm_create_tx(struct net_device *dev, struct ipoib_path *path,
				       struct ipoib_neigh *neigh)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_cm_tx *tx;

	tx = kzalloc(sizeof *tx, GFP_ATOMIC);
	if (!tx)
		return NULL;

	neigh->cm = tx;
	tx->neigh = neigh;
	tx->path = path;
	tx->dev = dev;
	list_add(&tx->list, &priv->cm.start_list);
	set_bit(IPOIB_FLAG_INITIALIZED, &tx->flags);
	queue_work(ipoib_workqueue, &priv->cm.start_task);
	return tx;
}