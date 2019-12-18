#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  state; struct sock* sk; } ;
struct sock {int sk_err; int /*<<< orphan*/  sk_ack_backlog; int /*<<< orphan*/  sk_sleep; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; int /*<<< orphan*/  itf; } ;
struct TYPE_5__ {TYPE_1__ sap_addr; } ;
struct atmsvc_msg {TYPE_2__ pvc; int /*<<< orphan*/  sap; int /*<<< orphan*/  local; int /*<<< orphan*/  svc; int /*<<< orphan*/  qos; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/  qos; int /*<<< orphan*/  sap; int /*<<< orphan*/  local; int /*<<< orphan*/  remote; } ;
struct TYPE_6__ {int sk_err; int /*<<< orphan*/  sk_sleep; } ;

/* Variables and functions */
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  ATM_VF_CLOSE ; 
 int /*<<< orphan*/  ATM_VF_HASQOS ; 
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int /*<<< orphan*/  ATM_VF_WAITING ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 int EUNATCH ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  as_accept ; 
 int /*<<< orphan*/  as_reject ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct atm_vcc*,struct atm_vcc*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sigd ; 
 int /*<<< orphan*/  sigd_enq (struct atm_vcc*,int /*<<< orphan*/ ,struct atm_vcc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigd_enq2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct atm_vcc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_atm (struct atm_vcc*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int svc_create (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vcc_connect (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int svc_accept(struct socket *sock,struct socket *newsock,int flags)
{
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	struct atmsvc_msg *msg;
	struct atm_vcc *old_vcc = ATM_SD(sock);
	struct atm_vcc *new_vcc;
	int error;

	lock_sock(sk);

	error = svc_create(sock_net(sk), newsock, 0, 0);
	if (error)
		goto out;

	new_vcc = ATM_SD(newsock);

	pr_debug("svc_accept %p -> %p\n",old_vcc,new_vcc);
	while (1) {
		DEFINE_WAIT(wait);

		prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);
		while (!(skb = skb_dequeue(&sk->sk_receive_queue)) &&
		       sigd) {
			if (test_bit(ATM_VF_RELEASED,&old_vcc->flags)) break;
			if (test_bit(ATM_VF_CLOSE,&old_vcc->flags)) {
				error = -sk->sk_err;
				break;
			}
			if (flags & O_NONBLOCK) {
				error = -EAGAIN;
				break;
			}
			release_sock(sk);
			schedule();
			lock_sock(sk);
			if (signal_pending(current)) {
				error = -ERESTARTSYS;
				break;
			}
			prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);
		}
		finish_wait(sk->sk_sleep, &wait);
		if (error)
			goto out;
		if (!skb) {
			error = -EUNATCH;
			goto out;
		}
		msg = (struct atmsvc_msg *) skb->data;
		new_vcc->qos = msg->qos;
		set_bit(ATM_VF_HASQOS,&new_vcc->flags);
		new_vcc->remote = msg->svc;
		new_vcc->local = msg->local;
		new_vcc->sap = msg->sap;
		error = vcc_connect(newsock, msg->pvc.sap_addr.itf,
				    msg->pvc.sap_addr.vpi, msg->pvc.sap_addr.vci);
		dev_kfree_skb(skb);
		sk->sk_ack_backlog--;
		if (error) {
			sigd_enq2(NULL,as_reject,old_vcc,NULL,NULL,
			    &old_vcc->qos,error);
			error = error == -EAGAIN ? -EBUSY : error;
			goto out;
		}
		/* wait should be short, so we ignore the non-blocking flag */
		set_bit(ATM_VF_WAITING, &new_vcc->flags);
		prepare_to_wait(sk_atm(new_vcc)->sk_sleep, &wait, TASK_UNINTERRUPTIBLE);
		sigd_enq(new_vcc,as_accept,old_vcc,NULL,NULL);
		while (test_bit(ATM_VF_WAITING, &new_vcc->flags) && sigd) {
			release_sock(sk);
			schedule();
			lock_sock(sk);
			prepare_to_wait(sk_atm(new_vcc)->sk_sleep, &wait, TASK_UNINTERRUPTIBLE);
		}
		finish_wait(sk_atm(new_vcc)->sk_sleep, &wait);
		if (!sigd) {
			error = -EUNATCH;
			goto out;
		}
		if (!sk_atm(new_vcc)->sk_err)
			break;
		if (sk_atm(new_vcc)->sk_err != ERESTARTSYS) {
			error = -sk_atm(new_vcc)->sk_err;
			goto out;
		}
	}
	newsock->state = SS_CONNECTED;
out:
	release_sock(sk);
	return error;
}