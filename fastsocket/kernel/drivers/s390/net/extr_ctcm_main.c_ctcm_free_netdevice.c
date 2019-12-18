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
struct net_device {struct ctcm_priv* ml_priv; int /*<<< orphan*/  name; } ;
struct mpc_group {int /*<<< orphan*/  mpc_tasklet2; scalar_t__ rcvd_xid_skb; scalar_t__ xid_skb; int /*<<< orphan*/ * fsm; } ;
struct ctcm_priv {struct mpc_group* xid; int /*<<< orphan*/ * fsm; struct mpc_group* mpcg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_INFO ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct mpc_group*) ; 
 int /*<<< orphan*/  kfree_fsm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ctcm_free_netdevice(struct net_device *dev)
{
	struct ctcm_priv *priv;
	struct mpc_group *grp;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"%s(%s)", CTCM_FUNTAIL, dev->name);
	priv = dev->ml_priv;
	if (priv) {
		grp = priv->mpcg;
		if (grp) {
			if (grp->fsm)
				kfree_fsm(grp->fsm);
			if (grp->xid_skb)
				dev_kfree_skb(grp->xid_skb);
			if (grp->rcvd_xid_skb)
				dev_kfree_skb(grp->rcvd_xid_skb);
			tasklet_kill(&grp->mpc_tasklet2);
			kfree(grp);
			priv->mpcg = NULL;
		}
		if (priv->fsm) {
			kfree_fsm(priv->fsm);
			priv->fsm = NULL;
		}
		kfree(priv->xid);
		priv->xid = NULL;
	/*
	 * Note: kfree(priv); is done in "opposite" function of
	 * allocator function probe_device which is remove_device.
	 */
	}
#ifdef MODULE
	free_netdev(dev);
#endif
}