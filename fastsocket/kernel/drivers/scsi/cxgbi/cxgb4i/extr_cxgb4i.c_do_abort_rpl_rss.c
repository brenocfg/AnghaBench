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
struct tid_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct cxgbi_sock {unsigned long flags; int /*<<< orphan*/  state; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cpl_abort_rpl_rss {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_ABORT_FAILED ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 unsigned int GET_TID (struct cpl_abort_rpl_rss*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_sock_rcv_abort_rpl (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  log_debug (int,char*,scalar_t__,struct cxgbi_sock*,int /*<<< orphan*/ ,unsigned long) ; 
 struct cxgbi_sock* lookup_tid (struct tid_info*,unsigned int) ; 

__attribute__((used)) static void do_abort_rpl_rss(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cxgbi_sock *csk;
	struct cpl_abort_rpl_rss *rpl = (struct cpl_abort_rpl_rss *)skb->data;
	unsigned int tid = GET_TID(rpl);
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;

	csk = lookup_tid(t, tid);
	if (!csk)
		goto rel_skb;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"status 0x%x, csk 0x%p, s %u, 0x%lx.\n",
		rpl->status, csk, csk ? csk->state : 0,
		csk ? csk->flags : 0UL);

	if (rpl->status == CPL_ERR_ABORT_FAILED)
		goto rel_skb;

	cxgbi_sock_rcv_abort_rpl(csk);
rel_skb:
	__kfree_skb(skb);
}