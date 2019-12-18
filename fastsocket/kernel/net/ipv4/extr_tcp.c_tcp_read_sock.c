#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tcp_sock {size_t copied_seq; size_t urg_seq; scalar_t__ urg_data; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {size_t len; } ;
typedef  int (* sk_read_actor_t ) (TYPE_1__*,struct sk_buff*,size_t,size_t) ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ read_descriptor_t ;
struct TYPE_7__ {scalar_t__ fin; } ;

/* Variables and functions */
 int ENOTCONN ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  sk_eat_skb (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_cleanup_rbuf (struct sock*,int) ; 
 TYPE_5__* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_rcv_space_adjust (struct sock*) ; 
 struct sk_buff* tcp_recv_skb (struct sock*,size_t,size_t*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

int tcp_read_sock(struct sock *sk, read_descriptor_t *desc,
		  sk_read_actor_t recv_actor)
{
	struct sk_buff *skb;
	struct tcp_sock *tp = tcp_sk(sk);
	u32 seq = tp->copied_seq;
	u32 offset;
	int copied = 0;

	if (sk->sk_state == TCP_LISTEN)
		return -ENOTCONN;
	while ((skb = tcp_recv_skb(sk, seq, &offset)) != NULL) {
		if (offset < skb->len) {
			int used;
			size_t len;

			len = skb->len - offset;
			/* Stop reading if we hit a patch of urgent data */
			if (tp->urg_data) {
				u32 urg_offset = tp->urg_seq - seq;
				if (urg_offset < len)
					len = urg_offset;
				if (!len)
					break;
			}
			used = recv_actor(desc, skb, offset, len);
			if (used < 0) {
				if (!copied)
					copied = used;
				break;
			} else if (used <= len) {
				seq += used;
				copied += used;
				offset += used;
			}
			/*
			 * If recv_actor drops the lock (e.g. TCP splice
			 * receive) the skb pointer might be invalid when
			 * getting here: tcp_collapse might have deleted it
			 * while aggregating skbs from the socket queue.
			 */
			skb = tcp_recv_skb(sk, seq-1, &offset);
			if (!skb || (offset+1 != skb->len))
				break;
		}
		if (tcp_hdr(skb)->fin) {
			sk_eat_skb(sk, skb, 0);
			++seq;
			break;
		}
		sk_eat_skb(sk, skb, 0);
		if (!desc->count)
			break;
		tp->copied_seq = seq;
	}
	tp->copied_seq = seq;

	tcp_rcv_space_adjust(sk);

	/* Clean up data we have read: This will do ACK frames. */
	if (copied > 0)
		tcp_cleanup_rbuf(sk, copied);
	return copied;
}