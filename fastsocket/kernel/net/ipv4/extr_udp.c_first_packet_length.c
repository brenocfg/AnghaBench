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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  UDP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_reclaim_partial (struct sock*) ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ udp_lib_checksum_complete (struct sk_buff*) ; 

__attribute__((used)) static unsigned int first_packet_length(struct sock *sk)
{
	struct sk_buff_head list_kill, *rcvq = &sk->sk_receive_queue;
	struct sk_buff *skb;
	unsigned int res;

	__skb_queue_head_init(&list_kill);

	spin_lock_bh(&rcvq->lock);
	while ((skb = skb_peek(rcvq)) != NULL &&
		udp_lib_checksum_complete(skb)) {
		UDP_INC_STATS_BH(sock_net(sk), UDP_MIB_INERRORS,
				 IS_UDPLITE(sk));
		__skb_unlink(skb, rcvq);
		__skb_queue_tail(&list_kill, skb);
	}
	res = skb ? skb->len : 0;
	spin_unlock_bh(&rcvq->lock);

	if (!skb_queue_empty(&list_kill)) {
		lock_sock(sk);
		__skb_queue_purge(&list_kill);
		sk_mem_reclaim_partial(sk);
		release_sock(sk);
	}
	return res;
}