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
struct net_device {int flags; int /*<<< orphan*/  mtu; } ;
struct neighbour {struct net_device* dev; } ;
struct dst_entry {int dummy; } ;
struct c4iw_ep {int smac_idx; int txq_idx; int ctrlq_idx; scalar_t__ tried_with_mpa_v1; scalar_t__ retry_with_mpa_v1; int /*<<< orphan*/  rss_qid; void* tx_chan; int /*<<< orphan*/  mtu; void* l2t; } ;
struct TYPE_3__ {int ntxq; int nchan; int nrxq; int /*<<< orphan*/ * rxq_ids; int /*<<< orphan*/  l2t; } ;
struct TYPE_4__ {TYPE_1__ lldi; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int IFF_LOOPBACK ; 
 void* cxgb4_l2t_get (int /*<<< orphan*/ ,struct neighbour*,struct net_device*,int /*<<< orphan*/ ) ; 
 void* cxgb4_port_chan (struct net_device*) ; 
 int cxgb4_port_idx (struct net_device*) ; 
 int cxgb4_port_viid (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct neighbour* dst_get_neighbour_noref (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* ip_dev_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int import_ep(struct c4iw_ep *ep, __be32 peer_ip, struct dst_entry *dst,
		     struct c4iw_dev *cdev, bool clear_mpa_v1)
{
	struct neighbour *n;
	int err, step;

	rcu_read_lock();
	n = dst_get_neighbour_noref(dst);
	err = -ENODEV;
	if (!n)
		goto out;
	err = -ENOMEM;
	if (n->dev->flags & IFF_LOOPBACK) {
		struct net_device *pdev;

		pdev = ip_dev_find(&init_net, peer_ip);
		if (!pdev) {
			err = -ENODEV;
			goto out;
		}
		ep->l2t = cxgb4_l2t_get(cdev->rdev.lldi.l2t,
					n, pdev, 0);
		if (!ep->l2t)
			goto out;
		ep->mtu = pdev->mtu;
		ep->tx_chan = cxgb4_port_chan(pdev);
		ep->smac_idx = (cxgb4_port_viid(pdev) & 0x7F) << 1;
		step = cdev->rdev.lldi.ntxq /
			cdev->rdev.lldi.nchan;
		ep->txq_idx = cxgb4_port_idx(pdev) * step;
		step = cdev->rdev.lldi.nrxq /
			cdev->rdev.lldi.nchan;
		ep->ctrlq_idx = cxgb4_port_idx(pdev);
		ep->rss_qid = cdev->rdev.lldi.rxq_ids[
			cxgb4_port_idx(pdev) * step];
		dev_put(pdev);
	} else {
		ep->l2t = cxgb4_l2t_get(cdev->rdev.lldi.l2t,
					n, n->dev, 0);
		if (!ep->l2t)
			goto out;
		ep->mtu = dst_mtu(dst);
		ep->tx_chan = cxgb4_port_chan(n->dev);
		ep->smac_idx = (cxgb4_port_viid(n->dev) & 0x7F) << 1;
		step = cdev->rdev.lldi.ntxq /
			cdev->rdev.lldi.nchan;
		ep->txq_idx = cxgb4_port_idx(n->dev) * step;
		ep->ctrlq_idx = cxgb4_port_idx(n->dev);
		step = cdev->rdev.lldi.nrxq /
			cdev->rdev.lldi.nchan;
		ep->rss_qid = cdev->rdev.lldi.rxq_ids[
			cxgb4_port_idx(n->dev) * step];

		if (clear_mpa_v1) {
			ep->retry_with_mpa_v1 = 0;
			ep->tried_with_mpa_v1 = 0;
		}
	}
	err = 0;
out:
	rcu_read_unlock();

	return err;
}