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
struct sock {int /*<<< orphan*/  sk_rcvbuf; } ;
struct sk_buff {int dummy; } ;
struct sctp_inq {int dummy; } ;
struct sctp_ep_common {scalar_t__ type; struct sock* sk; scalar_t__ dead; struct sctp_inq inqueue; } ;
struct sctp_chunk {struct sctp_ep_common* rcvr; } ;
struct TYPE_2__ {struct sctp_chunk* chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ SCTP_EP_TYPE_ASSOCIATION ; 
 scalar_t__ SCTP_EP_TYPE_SOCKET ; 
 TYPE_1__* SCTP_INPUT_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_assoc (struct sctp_ep_common*) ; 
 int /*<<< orphan*/  sctp_association_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  sctp_bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_endpoint_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ep (struct sctp_ep_common*) ; 
 int /*<<< orphan*/  sctp_inq_push (struct sctp_inq*,struct sctp_chunk*) ; 
 scalar_t__ sk_add_backlog (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

int sctp_backlog_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;
	struct sctp_inq *inqueue = &chunk->rcvr->inqueue;
	struct sctp_ep_common *rcvr = NULL;
	int backloged = 0;

	rcvr = chunk->rcvr;

	/* If the rcvr is dead then the association or endpoint
	 * has been deleted and we can safely drop the chunk
	 * and refs that we are holding.
	 */
	if (rcvr->dead) {
		sctp_chunk_free(chunk);
		goto done;
	}

	if (unlikely(rcvr->sk != sk)) {
		/* In this case, the association moved from one socket to
		 * another.  We are currently sitting on the backlog of the
		 * old socket, so we need to move.
		 * However, since we are here in the process context we
		 * need to take make sure that the user doesn't own
		 * the new socket when we process the packet.
		 * If the new socket is user-owned, queue the chunk to the
		 * backlog of the new socket without dropping any refs.
		 * Otherwise, we can safely push the chunk on the inqueue.
		 */

		sk = rcvr->sk;
		sctp_bh_lock_sock(sk);

		if (sock_owned_by_user(sk)) {
			if (sk_add_backlog(sk, skb, sk->sk_rcvbuf))
				sctp_chunk_free(chunk);
			else
				backloged = 1;
		} else
			sctp_inq_push(inqueue, chunk);

		sctp_bh_unlock_sock(sk);

		/* If the chunk was backloged again, don't drop refs */
		if (backloged)
			return 0;
	} else {
		sctp_inq_push(inqueue, chunk);
	}

done:
	/* Release the refs we took in sctp_add_backlog */
	if (SCTP_EP_TYPE_ASSOCIATION == rcvr->type)
		sctp_association_put(sctp_assoc(rcvr));
	else if (SCTP_EP_TYPE_SOCKET == rcvr->type)
		sctp_endpoint_put(sctp_ep(rcvr));
	else
		BUG();

	return 0;
}