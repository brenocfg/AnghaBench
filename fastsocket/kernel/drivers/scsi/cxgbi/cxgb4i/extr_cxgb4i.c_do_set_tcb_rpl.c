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
struct cxgbi_sock {int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {struct tid_info* tids; } ;
struct cpl_set_tcb_rpl {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 unsigned int GET_TID (struct cpl_set_tcb_rpl*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct cxgbi_sock* lookup_tid (struct tid_info*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void do_set_tcb_rpl(struct cxgbi_device *cdev, struct sk_buff *skb)
{
	struct cpl_set_tcb_rpl *rpl = (struct cpl_set_tcb_rpl *)skb->data;
	unsigned int tid = GET_TID(rpl);
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct tid_info *t = lldi->tids;
	struct cxgbi_sock *csk;

	csk = lookup_tid(t, tid);
	if (!csk)
		pr_err("can't find conn. for tid %u.\n", tid);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,%lx,%u, status 0x%x.\n",
		csk, csk->state, csk->flags, csk->tid, rpl->status);

	if (rpl->status != CPL_ERR_NONE)
		pr_err("csk 0x%p,%u, SET_TCB_RPL status %u.\n",
			csk, tid, rpl->status);

	__kfree_skb(skb);
}