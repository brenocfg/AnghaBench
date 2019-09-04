#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct mbuf* sb_mb; struct mbuf* sb_lastrecord; struct mbuf* sb_mbtail; } ;
struct socket {TYPE_2__ so_snd; TYPE_1__* so_msg_state; } ;
struct msg_priq {int msgq_flags; scalar_t__ msgq_bytes; struct mbuf* msgq_lastmsg; int /*<<< orphan*/ * msgq_tail; struct mbuf* msgq_head; } ;
struct mbuf {scalar_t__ m_len; int m_flags; struct mbuf* m_next; struct mbuf* m_nextpkt; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {scalar_t__ msg_serial_bytes; struct msg_priq* msg_priq; } ;

/* Variables and functions */
 int MSGQ_MSG_NOTDONE ; 
 scalar_t__ MSG_PRI_MAX ; 
 scalar_t__ MSG_PRI_MIN ; 
 int M_EOR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  sblastmbufchk (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sblastrecordchk (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sbwakeup (TYPE_2__*) ; 

void
sbpull_unordered_data(struct socket *so, int32_t off, int32_t len)
{
	int32_t topull, i;
	struct msg_priq *priq = NULL;

	VERIFY(so->so_msg_state != NULL);

	topull = (off + len) - so->so_msg_state->msg_serial_bytes;

	i = MSG_PRI_MAX;
	while (i >= MSG_PRI_MIN && topull > 0) {
		struct mbuf *m = NULL, *mqhead = NULL, *mend = NULL;
		priq = &so->so_msg_state->msg_priq[i];
		if ((priq->msgq_flags & MSGQ_MSG_NOTDONE) &&
		    priq->msgq_head == NULL) {
			/*
			 * We were in the middle of sending
			 * a message and we have not seen the
			 * end of it.
			 */
			VERIFY(priq->msgq_lastmsg == NULL &&
			    priq->msgq_tail == NULL);
			return;
		}
		if (priq->msgq_head != NULL) {
			int32_t bytes = 0, topull_tmp = topull;
			/*
			 * We found a msg while scanning the priority
			 * queue from high to low priority.
			 */
			m = priq->msgq_head;
			mqhead = m;
			mend = m;

			/*
			 * Move bytes from the priority queue to the
			 * serial queue. Compute the number of bytes
			 * being added.
			 */
			while (mqhead->m_next != NULL && topull_tmp > 0) {
				bytes += mqhead->m_len;
				topull_tmp -= mqhead->m_len;
				mend = mqhead;
				mqhead = mqhead->m_next;
			}

			if (mqhead->m_next == NULL) {
				/*
				 * If we have only one more mbuf left,
				 * move the last mbuf of this message to
				 * serial queue and set the head of the
				 * queue to be the next message.
				 */
				bytes += mqhead->m_len;
				mend = mqhead;
				mqhead = m->m_nextpkt;
				if (!(mend->m_flags & M_EOR)) {
					/*
					 * We have not seen the end of
					 * this message, so we can not
					 * pull anymore.
					 */
					priq->msgq_flags |= MSGQ_MSG_NOTDONE;
				} else {
					/* Reset M_EOR */
					mend->m_flags &= ~(M_EOR);
				}
			} else {
				/* propogate the next msg pointer */
				mqhead->m_nextpkt = m->m_nextpkt;
			}
			priq->msgq_head = mqhead;

			/*
			 * if the lastmsg pointer points to
			 * the mbuf that is being dequeued, update
			 * it to point to the new head.
			 */
			if (priq->msgq_lastmsg == m)
				priq->msgq_lastmsg = priq->msgq_head;

			m->m_nextpkt = NULL;
			mend->m_next = NULL;

			if (priq->msgq_head == NULL) {
				/* Moved all messages, update tail */
				priq->msgq_tail = NULL;
				VERIFY(priq->msgq_lastmsg == NULL);
			}

			/* Move it to serial sb_mb queue */
			if (so->so_snd.sb_mb == NULL) {
				so->so_snd.sb_mb = m;
			} else {
				so->so_snd.sb_mbtail->m_next = m;
			}

			priq->msgq_bytes -= bytes;
			VERIFY(priq->msgq_bytes >= 0);
			sbwakeup(&so->so_snd);

			so->so_msg_state->msg_serial_bytes += bytes;
			so->so_snd.sb_mbtail = mend;
			so->so_snd.sb_lastrecord = so->so_snd.sb_mb;

			topull =
			    (off + len) - so->so_msg_state->msg_serial_bytes;

			if (priq->msgq_flags & MSGQ_MSG_NOTDONE)
				break;
		} else {
			--i;
		}
	}
	sblastrecordchk(&so->so_snd, "sbpull_unordered_data");
	sblastmbufchk(&so->so_snd, "sbpull_unordered_data");
}