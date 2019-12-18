#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct rdma_dev_addr {scalar_t__ bound_dev_if; } ;
struct TYPE_6__ {struct rdma_dev_addr dev_addr; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;
struct TYPE_8__ {scalar_t__ ps; TYPE_2__ route; } ;
struct rdma_id_private {TYPE_3__ id; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct TYPE_9__ {int hop_limit; int /*<<< orphan*/  port_gid; int /*<<< orphan*/  mtu; int /*<<< orphan*/  rate; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey; int /*<<< orphan*/  mgid; } ;
struct iboe_mcast_work {int /*<<< orphan*/  work; struct cma_multicast* mc; struct rdma_id_private* id; TYPE_4__ rec; } ;
struct ib_sa_multicast {int dummy; } ;
struct TYPE_10__ {struct iboe_mcast_work* ib; } ;
struct cma_multicast {TYPE_5__ multicast; int /*<<< orphan*/  mcref; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RDMA_PS_UDP ; 
 int /*<<< orphan*/  RDMA_UDP_QKEY ; 
 int /*<<< orphan*/  cma_iboe_set_mgid (struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cma_wq ; 
 scalar_t__ cma_zero_addr (struct sockaddr*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  iboe_addr_get_sgid (struct rdma_dev_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iboe_get_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iboe_get_rate (struct net_device*) ; 
 int /*<<< orphan*/  iboe_mcast_work_handler ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree (struct iboe_mcast_work*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_iboe_join_multicast(struct rdma_id_private *id_priv,
				   struct cma_multicast *mc)
{
	struct iboe_mcast_work *work;
	struct rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	int err;
	struct sockaddr *addr = (struct sockaddr *)&mc->addr;
	struct net_device *ndev = NULL;

	if (cma_zero_addr((struct sockaddr *)&mc->addr))
		return -EINVAL;

	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (!work)
		return -ENOMEM;

	mc->multicast.ib = kzalloc(sizeof(struct ib_sa_multicast), GFP_KERNEL);
	if (!mc->multicast.ib) {
		err = -ENOMEM;
		goto out1;
	}

	cma_iboe_set_mgid(addr, &mc->multicast.ib->rec.mgid);

	mc->multicast.ib->rec.pkey = cpu_to_be16(0xffff);
	if (id_priv->id.ps == RDMA_PS_UDP)
		mc->multicast.ib->rec.qkey = cpu_to_be32(RDMA_UDP_QKEY);

	if (dev_addr->bound_dev_if)
		ndev = dev_get_by_index(&init_net, dev_addr->bound_dev_if);
	if (!ndev) {
		err = -ENODEV;
		goto out2;
	}
	mc->multicast.ib->rec.rate = iboe_get_rate(ndev);
	mc->multicast.ib->rec.hop_limit = 1;
	mc->multicast.ib->rec.mtu = iboe_get_mtu(ndev->mtu);
	dev_put(ndev);
	if (!mc->multicast.ib->rec.mtu) {
		err = -EINVAL;
		goto out2;
	}
	iboe_addr_get_sgid(dev_addr, &mc->multicast.ib->rec.port_gid);
	work->id = id_priv;
	work->mc = mc;
	INIT_WORK(&work->work, iboe_mcast_work_handler);
	kref_get(&mc->mcref);
	queue_work(cma_wq, &work->work);

	return 0;

out2:
	kfree(mc->multicast.ib);
out1:
	kfree(work);
	return err;
}