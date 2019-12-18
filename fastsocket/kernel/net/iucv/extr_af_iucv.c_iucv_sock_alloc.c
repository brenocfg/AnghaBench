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
struct socket {int dummy; } ;
struct sock {int sk_protocol; int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_destruct; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct iucv_sock {int /*<<< orphan*/  transport; int /*<<< orphan*/  src_user_id; int /*<<< orphan*/  sk_txnotify; int /*<<< orphan*/ * path; int /*<<< orphan*/  msg_recv; int /*<<< orphan*/  msg_sent; scalar_t__ msglimit; scalar_t__ flags; int /*<<< orphan*/  pendings; scalar_t__ send_tag; int /*<<< orphan*/  backlog_skb_q; TYPE_1__ message_q; int /*<<< orphan*/  send_skb_q; int /*<<< orphan*/  accept_q_lock; int /*<<< orphan*/  accept_q; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IUCV_TRANS_HIPER ; 
 int /*<<< orphan*/  AF_IUCV_TRANS_IUCV ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUCV_CONN_TIMEOUT ; 
 int /*<<< orphan*/  IUCV_OPEN ; 
 int /*<<< orphan*/  PF_IUCV ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  afiucv_hs_callback_txnotify ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  iucv_proto ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  iucv_sk_list ; 
 int /*<<< orphan*/  iucv_sock_destruct ; 
 int /*<<< orphan*/  iucv_sock_link (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_timeout ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pr_iucv ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct sock* sk_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sock *iucv_sock_alloc(struct socket *sock, int proto, gfp_t prio)
{
	struct sock *sk;
	struct iucv_sock *iucv;

	sk = sk_alloc(&init_net, PF_IUCV, prio, &iucv_proto);
	if (!sk)
		return NULL;
	iucv = iucv_sk(sk);

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&iucv->accept_q);
	spin_lock_init(&iucv->accept_q_lock);
	skb_queue_head_init(&iucv->send_skb_q);
	INIT_LIST_HEAD(&iucv->message_q.list);
	spin_lock_init(&iucv->message_q.lock);
	skb_queue_head_init(&iucv->backlog_skb_q);
	iucv->send_tag = 0;
	atomic_set(&iucv->pendings, 0);
	iucv->flags = 0;
	iucv->msglimit = 0;
	atomic_set(&iucv->msg_sent, 0);
	atomic_set(&iucv->msg_recv, 0);
	iucv->path = NULL;
	iucv->sk_txnotify = afiucv_hs_callback_txnotify;
	memset(&iucv->src_user_id , 0, 32);
	if (pr_iucv)
		iucv->transport = AF_IUCV_TRANS_IUCV;
	else
		iucv->transport = AF_IUCV_TRANS_HIPER;

	sk->sk_destruct = iucv_sock_destruct;
	sk->sk_sndtimeo = IUCV_CONN_TIMEOUT;
	sk->sk_allocation = GFP_DMA;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state	= IUCV_OPEN;

	setup_timer(&sk->sk_timer, iucv_sock_timeout, (unsigned long)sk);

	iucv_sock_link(&iucv_sk_list, sk);
	return sk;
}