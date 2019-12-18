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
struct sock {int /*<<< orphan*/  sk_wmem_queued; int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {scalar_t__ truesize; scalar_t__ cb; } ;
struct sctp_chunk {struct sctp_association* asoc; } ;
struct TYPE_2__ {struct sock* sk; } ;
struct sctp_association {int /*<<< orphan*/  sndbuf_used; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ SCTP_DATA_SNDSIZE (struct sctp_chunk*) ; 
 int /*<<< orphan*/  __sctp_write_space (struct sctp_association*) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_put (struct sctp_association*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,scalar_t__) ; 
 int /*<<< orphan*/  sock_wfree (struct sk_buff*) ; 

__attribute__((used)) static void sctp_wfree(struct sk_buff *skb)
{
	struct sctp_association *asoc;
	struct sctp_chunk *chunk;
	struct sock *sk;

	/* Get the saved chunk pointer.  */
	chunk = *((struct sctp_chunk **)(skb->cb));
	asoc = chunk->asoc;
	sk = asoc->base.sk;
	asoc->sndbuf_used -= SCTP_DATA_SNDSIZE(chunk) +
				sizeof(struct sk_buff) +
				sizeof(struct sctp_chunk);

	atomic_sub(sizeof(struct sctp_chunk), &sk->sk_wmem_alloc);

	/*
	 * This undoes what is done via sctp_set_owner_w and sk_mem_charge
	 */
	sk->sk_wmem_queued   -= skb->truesize;
	sk_mem_uncharge(sk, skb->truesize);

	sock_wfree(skb);
	__sctp_write_space(asoc);

	sctp_association_put(asoc);
}