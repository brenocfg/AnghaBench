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
struct msg_priq {scalar_t__ msgq_flags; scalar_t__ msgq_bytes; int /*<<< orphan*/ * msgq_lastmsg; struct mbuf* msgq_tail; struct mbuf* msgq_head; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem_list (struct mbuf*) ; 

__attribute__((used)) static void
sbflush_priq(struct msg_priq *priq)
{
	struct mbuf *m;
	m = priq->msgq_head;
	if (m != NULL)
		m_freem_list(m);
	priq->msgq_head = priq->msgq_tail = priq->msgq_lastmsg = NULL;
	priq->msgq_bytes = priq->msgq_flags = 0;
}