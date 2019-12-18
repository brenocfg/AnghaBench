#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {TYPE_1__ mgid; } ;
struct ipoib_mcast {int backoff; int /*<<< orphan*/  mc; int /*<<< orphan*/  flags; TYPE_2__ mcmember; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  mcast_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; TYPE_4__* broadcast; int /*<<< orphan*/  pkey; int /*<<< orphan*/  local_gid; } ;
struct ib_sa_mcmember_rec {int join_state; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  sl; int /*<<< orphan*/  rate; void* rate_selector; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  mtu; void* mtu_selector; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey; int /*<<< orphan*/  port_gid; TYPE_1__ mgid; } ;
typedef  int ib_sa_comp_mask ;
struct TYPE_7__ {int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  sl; int /*<<< orphan*/  rate; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  mtu; int /*<<< orphan*/  qkey; } ;
struct TYPE_8__ {TYPE_3__ mcmember; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 void* IB_SA_EQ ; 
 int IB_SA_MCMEMBER_REC_FLOW_LABEL ; 
 int IB_SA_MCMEMBER_REC_HOP_LIMIT ; 
 int IB_SA_MCMEMBER_REC_JOIN_STATE ; 
 int IB_SA_MCMEMBER_REC_MGID ; 
 int IB_SA_MCMEMBER_REC_MTU ; 
 int IB_SA_MCMEMBER_REC_MTU_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_PKEY ; 
 int IB_SA_MCMEMBER_REC_PORT_GID ; 
 int IB_SA_MCMEMBER_REC_QKEY ; 
 int IB_SA_MCMEMBER_REC_RATE ; 
 int IB_SA_MCMEMBER_REC_RATE_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_SL ; 
 int IB_SA_MCMEMBER_REC_TRAFFIC_CLASS ; 
 int IPOIB_MAX_BACKOFF_SECONDS ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  IPOIB_MCAST_RUN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_sa_join_multicast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sa_mcmember_rec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipoib_mcast*) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_mcast_join_complete ; 
 int /*<<< orphan*/  ipoib_sa_client ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  mcast_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_mcast_join(struct net_device *dev, struct ipoib_mcast *mcast,
			     int create)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ib_sa_mcmember_rec rec = {
		.join_state = 1
	};
	ib_sa_comp_mask comp_mask;
	int ret = 0;

	ipoib_dbg_mcast(priv, "joining MGID %pI6\n", mcast->mcmember.mgid.raw);

	rec.mgid     = mcast->mcmember.mgid;
	rec.port_gid = priv->local_gid;
	rec.pkey     = cpu_to_be16(priv->pkey);

	comp_mask =
		IB_SA_MCMEMBER_REC_MGID		|
		IB_SA_MCMEMBER_REC_PORT_GID	|
		IB_SA_MCMEMBER_REC_PKEY		|
		IB_SA_MCMEMBER_REC_JOIN_STATE;

	if (create) {
		comp_mask |=
			IB_SA_MCMEMBER_REC_QKEY			|
			IB_SA_MCMEMBER_REC_MTU_SELECTOR		|
			IB_SA_MCMEMBER_REC_MTU			|
			IB_SA_MCMEMBER_REC_TRAFFIC_CLASS	|
			IB_SA_MCMEMBER_REC_RATE_SELECTOR	|
			IB_SA_MCMEMBER_REC_RATE			|
			IB_SA_MCMEMBER_REC_SL			|
			IB_SA_MCMEMBER_REC_FLOW_LABEL		|
			IB_SA_MCMEMBER_REC_HOP_LIMIT;

		rec.qkey	  = priv->broadcast->mcmember.qkey;
		rec.mtu_selector  = IB_SA_EQ;
		rec.mtu		  = priv->broadcast->mcmember.mtu;
		rec.traffic_class = priv->broadcast->mcmember.traffic_class;
		rec.rate_selector = IB_SA_EQ;
		rec.rate	  = priv->broadcast->mcmember.rate;
		rec.sl		  = priv->broadcast->mcmember.sl;
		rec.flow_label	  = priv->broadcast->mcmember.flow_label;
		rec.hop_limit	  = priv->broadcast->mcmember.hop_limit;
	}

	set_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);
	mcast->mc = ib_sa_join_multicast(&ipoib_sa_client, priv->ca, priv->port,
					 &rec, comp_mask, GFP_KERNEL,
					 ipoib_mcast_join_complete, mcast);
	if (IS_ERR(mcast->mc)) {
		clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);
		ret = PTR_ERR(mcast->mc);
		ipoib_warn(priv, "ib_sa_join_multicast failed, status %d\n", ret);

		mcast->backoff *= 2;
		if (mcast->backoff > IPOIB_MAX_BACKOFF_SECONDS)
			mcast->backoff = IPOIB_MAX_BACKOFF_SECONDS;

		mutex_lock(&mcast_mutex);
		if (test_bit(IPOIB_MCAST_RUN, &priv->flags))
			queue_delayed_work(ipoib_workqueue,
					   &priv->mcast_task,
					   mcast->backoff * HZ);
		mutex_unlock(&mcast_mutex);
	}
}