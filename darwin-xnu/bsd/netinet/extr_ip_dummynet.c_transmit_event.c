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
typedef  scalar_t__ u_int64_t ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct dn_pkt_tag {scalar_t__ dn_output_time; } ;
struct dn_pipe {struct mbuf* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DN_KEY_LEQ (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ curr_time ; 
 int /*<<< orphan*/  dn_mutex ; 
 struct dn_pkt_tag* dn_tag_get (struct mbuf*) ; 
 int /*<<< orphan*/  extract_heap ; 
 int /*<<< orphan*/  heap_insert (int /*<<< orphan*/ *,scalar_t__,struct dn_pipe*) ; 
 scalar_t__ serialize ; 

__attribute__((used)) static void
transmit_event(struct dn_pipe *pipe, struct mbuf **head, struct mbuf **tail)
{
	struct mbuf *m ;
	struct dn_pkt_tag *pkt = NULL;
	u_int64_t schedule_time;

	LCK_MTX_ASSERT(dn_mutex, LCK_MTX_ASSERT_OWNED);
        ASSERT(serialize >= 0);
	if (serialize == 0) {
		while ((m = pipe->head) != NULL) {
			pkt = dn_tag_get(m);
			if (!DN_KEY_LEQ(pkt->dn_output_time, curr_time))
				break;

			pipe->head = m->m_nextpkt;
			if (*tail != NULL)
				(*tail)->m_nextpkt = m;
			else
				*head = m;
			*tail = m;
		}

		if (*tail != NULL)
			(*tail)->m_nextpkt = NULL;
	}

	schedule_time = pkt == NULL || DN_KEY_LEQ(pkt->dn_output_time, curr_time) ?
		curr_time + 1 : pkt->dn_output_time;

	/* if there are leftover packets, put the pipe into the heap for next ready event */
	if ((m = pipe->head) != NULL) {
		pkt = dn_tag_get(m);
		/* XXX should check errors on heap_insert, by draining the
		 * whole pipe p and hoping in the future we are more successful
		 */
		heap_insert(&extract_heap, schedule_time, pipe);
	}
}