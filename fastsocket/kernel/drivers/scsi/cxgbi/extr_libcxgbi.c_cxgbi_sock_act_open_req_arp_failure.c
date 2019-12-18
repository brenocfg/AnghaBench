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
struct sk_buff {scalar_t__ sk; } ;
struct cxgbi_sock {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CTP_ACTIVE_OPEN ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_sock_fail_act_open (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cxgbi_sock_act_open_req_arp_failure(void *handle, struct sk_buff *skb)
{
	struct cxgbi_sock *csk = (struct cxgbi_sock *)skb->sk;

	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);
	if (csk->state == CTP_ACTIVE_OPEN)
		cxgbi_sock_fail_act_open(csk, -EHOSTUNREACH);
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
	__kfree_skb(skb);
}