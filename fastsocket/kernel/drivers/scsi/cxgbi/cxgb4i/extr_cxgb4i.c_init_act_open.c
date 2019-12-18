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
struct sock {int dummy; } ;
struct sk_buff {struct sock* sk; } ;
struct port_info {int /*<<< orphan*/  port_id; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct cxgbi_sock {size_t port_id; scalar_t__ atid; int smac_idx; unsigned int txq_idx; int /*<<< orphan*/  l2t; int /*<<< orphan*/  mss_idx; scalar_t__ mtu; int /*<<< orphan*/  rss_qid; int /*<<< orphan*/  tx_chan; scalar_t__ err; scalar_t__ wr_una_cred; int /*<<< orphan*/  wr_cred; int /*<<< orphan*/  wr_max_cred; TYPE_1__* dst; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; struct cxgbi_device* cdev; } ;
struct cxgbi_device {struct net_device** ports; } ;
struct cxgb4_lld_info {unsigned int ntxq; unsigned int nchan; unsigned int nrxq; int /*<<< orphan*/  wr_cred; int /*<<< orphan*/ * rxq_ids; int /*<<< orphan*/  mtus; int /*<<< orphan*/  l2t; int /*<<< orphan*/  tids; } ;
struct cpl_act_open_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  neighbour; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_HAS_ATID ; 
 int /*<<< orphan*/  CTP_ACTIVE_OPEN ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct sk_buff* alloc_wr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cxgb4_alloc_atid (int /*<<< orphan*/ ,struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgb4_best_mtu (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb4_l2t_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_port_chan (struct net_device*) ; 
 unsigned int cxgb4_port_idx (struct net_device*) ; 
 int cxgb4_port_viid (struct net_device*) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_sock_act_open_req_arp_failure ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_reset_wr_list (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ dst_mtu (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_act_open_req (struct cxgbi_sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_arp_err_handler (struct sk_buff*,struct cxgbi_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_act_open(struct cxgbi_sock *csk)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct net_device *ndev = cdev->ports[csk->port_id];
	struct port_info *pi = netdev_priv(ndev);
	struct sk_buff *skb = NULL;
	unsigned int step;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	csk->atid = cxgb4_alloc_atid(lldi->tids, csk);
	if (csk->atid < 0) {
		pr_err("%s, NO atid available.\n", ndev->name);
		return -EINVAL;
	}
	cxgbi_sock_set_flag(csk, CTPF_HAS_ATID);
	cxgbi_sock_get(csk);

	csk->l2t = cxgb4_l2t_get(lldi->l2t, csk->dst->neighbour, ndev, 0);
	if (!csk->l2t) {
		pr_err("%s, cannot alloc l2t.\n", ndev->name);
		goto rel_resource;
	}
	cxgbi_sock_get(csk);

	skb = alloc_wr(sizeof(struct cpl_act_open_req), 0, GFP_KERNEL);
	if (!skb)
		goto rel_resource;
	skb->sk = (struct sock *)csk;
	t4_set_arp_err_handler(skb, csk, cxgbi_sock_act_open_req_arp_failure);

	if (!csk->mtu)
		csk->mtu = dst_mtu(csk->dst);
	cxgb4_best_mtu(lldi->mtus, csk->mtu, &csk->mss_idx);
	csk->tx_chan = cxgb4_port_chan(ndev);
	/* SMT two entries per row */
	csk->smac_idx = ((cxgb4_port_viid(ndev) & 0x7F)) << 1;
	step = lldi->ntxq / lldi->nchan;
	csk->txq_idx = cxgb4_port_idx(ndev) * step;
	step = lldi->nrxq / lldi->nchan;
	csk->rss_qid = lldi->rxq_ids[cxgb4_port_idx(ndev) * step];
	csk->wr_max_cred = csk->wr_cred = lldi->wr_cred;
	csk->wr_una_cred = 0;
	cxgbi_sock_reset_wr_list(csk);
	csk->err = 0;
	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,p%d,%s, %u,%u,%u, mss %u,%u, smac %u.\n",
		csk, pi->port_id, ndev->name, csk->tx_chan,
		csk->txq_idx, csk->rss_qid, csk->mtu, csk->mss_idx,
		csk->smac_idx);

	cxgbi_sock_set_state(csk, CTP_ACTIVE_OPEN);
	send_act_open_req(csk, skb, csk->l2t);
	return 0;

rel_resource:
	if (skb)
		__kfree_skb(skb);
	return -EINVAL;
}