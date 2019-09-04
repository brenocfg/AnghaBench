#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct socket {TYPE_2__* so_proto; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int m_flags; scalar_t__ m_type; struct mbuf* m_next; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_send ) (struct socket*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr*,struct mbuf*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ MT_CONTROL ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ ,struct mbuf*,struct sockaddr*,struct mbuf*,int /*<<< orphan*/ ) ; 

int
sosend_reinject(struct socket *so, struct sockaddr *addr, struct mbuf *top, struct mbuf *control, uint32_t sendflags)
{
	struct mbuf *m0, *control_end;

	socket_lock_assert_owned(so);

	/*
	 * top must points to mbuf chain to be sent.
	 * If control is not NULL, top must be packet header
	 */
	VERIFY(top != NULL &&
		   (control == NULL || top->m_flags & M_PKTHDR));

	/*
	 * If control is not passed in, see if we can get it
	 * from top.
	 */
	if (control == NULL && (top->m_flags & M_PKTHDR) == 0) {
		// Locate start of control if present and start of data
		for (m0 = top; m0 != NULL; m0 = m0->m_next) {
			if (m0->m_flags & M_PKTHDR) {
				top = m0;
				break;
			} else if (m0->m_type == MT_CONTROL) {
				if (control == NULL) {
					// Found start of control
					control = m0;
				}
				if (control != NULL && m0->m_next != NULL && m0->m_next->m_type != MT_CONTROL) {
					// Found end of control
					control_end = m0;
				}
			}
		}
		if (control_end != NULL)
			control_end->m_next = NULL;
	}

	int error = (*so->so_proto->pr_usrreqs->pru_send)
			(so, sendflags, top, addr, control, current_proc());

	return error;
}