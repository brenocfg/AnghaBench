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
struct net_device {int dummy; } ;
struct TYPE_4__ {int num_frags; } ;
struct ipoib_dev_priv {TYPE_2__ cm; TYPE_1__* mr; } ;
struct ib_sge {int /*<<< orphan*/  length; int /*<<< orphan*/  lkey; } ;
struct ib_recv_wr {int num_sge; struct ib_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct TYPE_3__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_CM_HEAD_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ipoib_cm_init_rx_wr(struct net_device *dev,
				struct ib_recv_wr *wr,
				struct ib_sge *sge)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < priv->cm.num_frags; ++i)
		sge[i].lkey = priv->mr->lkey;

	sge[0].length = IPOIB_CM_HEAD_SIZE;
	for (i = 1; i < priv->cm.num_frags; ++i)
		sge[i].length = PAGE_SIZE;

	wr->next    = NULL;
	wr->sg_list = sge;
	wr->num_sge = priv->cm.num_frags;
}