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
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_sleep; } ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/  qos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_VF_REGIS ; 
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  as_close ; 
 int /*<<< orphan*/  as_reject ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ sigd ; 
 int /*<<< orphan*/  sigd_enq (struct atm_vcc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigd_enq2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct atm_vcc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sock* sk_atm (struct atm_vcc*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void svc_disconnect(struct atm_vcc *vcc)
{
	DEFINE_WAIT(wait);
	struct sk_buff *skb;
	struct sock *sk = sk_atm(vcc);

	pr_debug("svc_disconnect %p\n",vcc);
	if (test_bit(ATM_VF_REGIS,&vcc->flags)) {
		prepare_to_wait(sk->sk_sleep, &wait, TASK_UNINTERRUPTIBLE);
		sigd_enq(vcc,as_close,NULL,NULL,NULL);
		while (!test_bit(ATM_VF_RELEASED,&vcc->flags) && sigd) {
			schedule();
			prepare_to_wait(sk->sk_sleep, &wait, TASK_UNINTERRUPTIBLE);
		}
		finish_wait(sk->sk_sleep, &wait);
	}
	/* beware - socket is still in use by atmsigd until the last
	   as_indicate has been answered */
	while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		atm_return(vcc, skb->truesize);
		pr_debug("LISTEN REL\n");
		sigd_enq2(NULL,as_reject,vcc,NULL,NULL,&vcc->qos,0);
		dev_kfree_skb(skb);
	}
	clear_bit(ATM_VF_REGIS, &vcc->flags);
	/* ... may retry later */
}