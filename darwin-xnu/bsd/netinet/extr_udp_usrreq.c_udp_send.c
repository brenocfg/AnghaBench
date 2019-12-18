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
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct mbuf {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int flow_divert_implicit_data_out (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ necp_socket_should_use_flow_divert (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int udp_output (struct inpcb*,struct mbuf*,struct sockaddr*,struct mbuf*,struct proc*) ; 

int
udp_send(struct socket *so, int flags, struct mbuf *m,
    struct sockaddr *addr, struct mbuf *control, struct proc *p)
{
#ifndef FLOW_DIVERT
#pragma unused(flags)
#endif /* !(FLOW_DIVERT) */
	struct inpcb *inp;

	inp = sotoinpcb(so);
	if (inp == NULL) {
		if (m != NULL)
			m_freem(m);
		if (control != NULL)
			m_freem(control);
		return (EINVAL);
	}

#if NECP
#if FLOW_DIVERT
	if (necp_socket_should_use_flow_divert(inp)) {
		/* Implicit connect */
		return (flow_divert_implicit_data_out(so, flags, m, addr,
		    control, p));
	}
#endif /* FLOW_DIVERT */
#endif /* NECP */

	return (udp_output(inp, m, addr, control, p));
}