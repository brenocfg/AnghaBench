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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct nr_sock {int /*<<< orphan*/  frag_queue; int /*<<< orphan*/  reseq_queue; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 struct nr_sock* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void nr_clear_queues(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);

	skb_queue_purge(&sk->sk_write_queue);
	skb_queue_purge(&nr->ack_queue);
	skb_queue_purge(&nr->reseq_queue);
	skb_queue_purge(&nr->frag_queue);
}