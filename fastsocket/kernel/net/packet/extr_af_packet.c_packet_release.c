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
struct tpacket_req {int dummy; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_prot; } ;
struct TYPE_6__ {scalar_t__ pg_vec; } ;
struct TYPE_5__ {scalar_t__ pg_vec; } ;
struct packet_sock {TYPE_3__ tx_ring; TYPE_2__ rx_ring; scalar_t__ num; scalar_t__ running; int /*<<< orphan*/  prot_hook; } ;
struct TYPE_4__ {int /*<<< orphan*/  sklist_lock; } ;
struct net {TYPE_1__ packet; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  dev_remove_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tpacket_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  packet_flush_mclist (struct sock*) ; 
 int /*<<< orphan*/  packet_set_ring (struct sock*,struct tpacket_req*,int,int) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  sk_refcnt_debug_release (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int packet_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct packet_sock *po;
	struct net *net;
#ifdef CONFIG_PACKET_MMAP
	struct tpacket_req req;
#endif

	if (!sk)
		return 0;

	net = sock_net(sk);
	po = pkt_sk(sk);

	write_lock_bh(&net->packet.sklist_lock);
	sk_del_node_init(sk);
	sock_prot_inuse_add(net, sk->sk_prot, -1);
	write_unlock_bh(&net->packet.sklist_lock);

	/*
	 *	Unhook packet receive handler.
	 */

	if (po->running) {
		/*
		 *	Remove the protocol hook
		 */
		dev_remove_pack(&po->prot_hook);
		po->running = 0;
		po->num = 0;
		__sock_put(sk);
	}

	packet_flush_mclist(sk);

#ifdef CONFIG_PACKET_MMAP
	memset(&req, 0, sizeof(req));

	if (po->rx_ring.pg_vec)
		packet_set_ring(sk, &req, 1, 0);

	if (po->tx_ring.pg_vec)
		packet_set_ring(sk, &req, 1, 1);
#endif

	/*
	 *	Now the socket is dead. No more input will appear.
	 */

	sock_orphan(sk);
	sock->sk = NULL;

	/* Purge queues */

	skb_queue_purge(&sk->sk_receive_queue);
	sk_refcnt_debug_release(sk);

	sock_put(sk);
	return 0;
}