#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr_dn {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_dst_cache; int /*<<< orphan*/  sk_ack_backlog; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {unsigned char* data; int /*<<< orphan*/  len; } ;
struct optdata_dn {int dummy; } ;
struct dst_entry {int dummy; } ;
struct dn_skb_cb {int services; int segsize; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  info; int /*<<< orphan*/  src_port; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {scalar_t__ a_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  sdn_flags; TYPE_1__ sdn_add; } ;
struct TYPE_8__ {scalar_t__ state; int services_rem; int segsize_rem; scalar_t__ accept_mode; TYPE_2__ discdata_out; TYPE_2__ conndata_out; TYPE_2__ peer; int /*<<< orphan*/  conndata_in; int /*<<< orphan*/  accessdata; TYPE_2__ addr; int /*<<< orphan*/  max_window; int /*<<< orphan*/  info_rem; int /*<<< orphan*/  addrrem; } ;

/* Variables and functions */
 scalar_t__ ACC_IMMED ; 
 scalar_t__ DN_CR ; 
 unsigned char DN_MENUVER_ACC ; 
 unsigned char DN_MENUVER_PRX ; 
 unsigned char DN_MENUVER_UIC ; 
 unsigned char DN_MENUVER_USR ; 
 scalar_t__ DN_O ; 
 TYPE_5__* DN_SK (struct sock*) ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int EINVAL ; 
 int ENOBUFS ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NSP_FC_MASK ; 
 int NSP_FC_NONE ; 
 int O_NONBLOCK ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SDF_PROXY ; 
 int /*<<< orphan*/  SDF_UICPROXY ; 
 int /*<<< orphan*/  SDF_WILD ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  decnet_no_fc_max_cwnd ; 
 int /*<<< orphan*/  dn_access_copy (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct sock* dn_alloc_sock (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 
 int dn_confirm_accept (struct sock*,long*,int /*<<< orphan*/ ) ; 
 int dn_hash_sock (struct sock*) ; 
 int /*<<< orphan*/  dn_send_conn_ack (struct sock*) ; 
 int /*<<< orphan*/  dn_user_copy (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int dn_username2sockaddr (unsigned char*,int /*<<< orphan*/ ,TYPE_2__*,unsigned char*) ; 
 struct sk_buff* dn_wait_for_connect (struct sock*,long*) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,struct dst_entry*) ; 

__attribute__((used)) static int dn_accept(struct socket *sock, struct socket *newsock, int flags)
{
	struct sock *sk = sock->sk, *newsk;
	struct sk_buff *skb = NULL;
	struct dn_skb_cb *cb;
	unsigned char menuver;
	int err = 0;
	unsigned char type;
	long timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);
	struct dst_entry *dst;

	lock_sock(sk);

	if (sk->sk_state != TCP_LISTEN || DN_SK(sk)->state != DN_O) {
		release_sock(sk);
		return -EINVAL;
	}

	skb = skb_dequeue(&sk->sk_receive_queue);
	if (skb == NULL) {
		skb = dn_wait_for_connect(sk, &timeo);
		if (IS_ERR(skb)) {
			release_sock(sk);
			return PTR_ERR(skb);
		}
	}

	cb = DN_SKB_CB(skb);
	sk->sk_ack_backlog--;
	newsk = dn_alloc_sock(sock_net(sk), newsock, sk->sk_allocation);
	if (newsk == NULL) {
		release_sock(sk);
		kfree_skb(skb);
		return -ENOBUFS;
	}
	release_sock(sk);

	dst = skb_dst(skb);
	dst_release(xchg(&newsk->sk_dst_cache, dst));
	skb_dst_set(skb, NULL);

	DN_SK(newsk)->state        = DN_CR;
	DN_SK(newsk)->addrrem      = cb->src_port;
	DN_SK(newsk)->services_rem = cb->services;
	DN_SK(newsk)->info_rem     = cb->info;
	DN_SK(newsk)->segsize_rem  = cb->segsize;
	DN_SK(newsk)->accept_mode  = DN_SK(sk)->accept_mode;

	if (DN_SK(newsk)->segsize_rem < 230)
		DN_SK(newsk)->segsize_rem = 230;

	if ((DN_SK(newsk)->services_rem & NSP_FC_MASK) == NSP_FC_NONE)
		DN_SK(newsk)->max_window = decnet_no_fc_max_cwnd;

	newsk->sk_state  = TCP_LISTEN;
	memcpy(&(DN_SK(newsk)->addr), &(DN_SK(sk)->addr), sizeof(struct sockaddr_dn));

	/*
	 * If we are listening on a wild socket, we don't want
	 * the newly created socket on the wrong hash queue.
	 */
	DN_SK(newsk)->addr.sdn_flags &= ~SDF_WILD;

	skb_pull(skb, dn_username2sockaddr(skb->data, skb->len, &(DN_SK(newsk)->addr), &type));
	skb_pull(skb, dn_username2sockaddr(skb->data, skb->len, &(DN_SK(newsk)->peer), &type));
	*(__le16 *)(DN_SK(newsk)->peer.sdn_add.a_addr) = cb->src;
	*(__le16 *)(DN_SK(newsk)->addr.sdn_add.a_addr) = cb->dst;

	menuver = *skb->data;
	skb_pull(skb, 1);

	if (menuver & DN_MENUVER_ACC)
		dn_access_copy(skb, &(DN_SK(newsk)->accessdata));

	if (menuver & DN_MENUVER_USR)
		dn_user_copy(skb, &(DN_SK(newsk)->conndata_in));

	if (menuver & DN_MENUVER_PRX)
		DN_SK(newsk)->peer.sdn_flags |= SDF_PROXY;

	if (menuver & DN_MENUVER_UIC)
		DN_SK(newsk)->peer.sdn_flags |= SDF_UICPROXY;

	kfree_skb(skb);

	memcpy(&(DN_SK(newsk)->conndata_out), &(DN_SK(sk)->conndata_out),
		sizeof(struct optdata_dn));
	memcpy(&(DN_SK(newsk)->discdata_out), &(DN_SK(sk)->discdata_out),
		sizeof(struct optdata_dn));

	lock_sock(newsk);
	err = dn_hash_sock(newsk);
	if (err == 0) {
		sock_reset_flag(newsk, SOCK_ZAPPED);
		dn_send_conn_ack(newsk);

		/*
		 * Here we use sk->sk_allocation since although the conn conf is
		 * for the newsk, the context is the old socket.
		 */
		if (DN_SK(newsk)->accept_mode == ACC_IMMED)
			err = dn_confirm_accept(newsk, &timeo,
						sk->sk_allocation);
	}
	release_sock(newsk);
	return err;
}