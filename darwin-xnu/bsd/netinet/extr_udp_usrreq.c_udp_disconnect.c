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
struct socket {int /*<<< orphan*/  so_state; } ;
struct TYPE_4__ {scalar_t__ s_addr; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct inpcb {int /*<<< orphan*/ * inp_last_outifp; TYPE_2__ inp_laddr; TYPE_1__ inp_faddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EPROTOTYPE ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  SS_ISCONNECTED ; 
 int /*<<< orphan*/  in_pcbdisconnect (struct inpcb*) ; 
 int /*<<< orphan*/  inp_reset_fc_state (struct inpcb*) ; 
 scalar_t__ necp_socket_should_use_flow_divert (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
udp_disconnect(struct socket *so)
{
	struct inpcb *inp;

	inp = sotoinpcb(so);
	if (inp == NULL
#if NECP
		|| (necp_socket_should_use_flow_divert(inp))
#endif /* NECP */
		)
		return (inp == NULL ? EINVAL : EPROTOTYPE);
	if (inp->inp_faddr.s_addr == INADDR_ANY)
		return (ENOTCONN);

	in_pcbdisconnect(inp);

	/* reset flow controlled state, just in case */
	inp_reset_fc_state(inp);

	inp->inp_laddr.s_addr = INADDR_ANY;
	so->so_state &= ~SS_ISCONNECTED;		/* XXX */
	inp->inp_last_outifp = NULL;

	return (0);
}