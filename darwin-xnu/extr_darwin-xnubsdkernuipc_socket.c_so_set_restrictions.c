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
typedef  int uint32_t ;
struct socket {int so_restrictions; } ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_MULTIPATH ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 int SO_RESTRICT_DENY_CELLULAR ; 
 int SO_RESTRICT_DENY_EXPENSIVE ; 
 int SO_RESTRICT_DENY_IN ; 
 int SO_RESTRICT_DENY_OUT ; 
 int /*<<< orphan*/  inp_set_nocellular (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inp_set_noexpensive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptcp_set_restrictions (struct socket*) ; 
 int /*<<< orphan*/  sotoinpcb (struct socket*) ; 

int
so_set_restrictions(struct socket *so, uint32_t vals)
{
	int nocell_old, nocell_new;
	int noexpensive_old, noexpensive_new;

	/*
	 * Deny-type restrictions are trapdoors; once set they cannot be
	 * unset for the lifetime of the socket.  This allows them to be
	 * issued by a framework on behalf of the application without
	 * having to worry that they can be undone.
	 *
	 * Note here that socket-level restrictions overrides any protocol
	 * level restrictions.  For instance, SO_RESTRICT_DENY_CELLULAR
	 * socket restriction issued on the socket has a higher precendence
	 * than INP_NO_IFT_CELLULAR.  The latter is affected by the UUID
	 * policy PROC_UUID_NO_CELLULAR for unrestricted sockets only,
	 * i.e. when SO_RESTRICT_DENY_CELLULAR has not been issued.
	 */
	nocell_old = (so->so_restrictions & SO_RESTRICT_DENY_CELLULAR);
	noexpensive_old = (so->so_restrictions & SO_RESTRICT_DENY_EXPENSIVE);
	so->so_restrictions |= (vals & (SO_RESTRICT_DENY_IN |
	    SO_RESTRICT_DENY_OUT | SO_RESTRICT_DENY_CELLULAR |
	    SO_RESTRICT_DENY_EXPENSIVE));
	nocell_new = (so->so_restrictions & SO_RESTRICT_DENY_CELLULAR);
	noexpensive_new = (so->so_restrictions & SO_RESTRICT_DENY_EXPENSIVE);

	/* we can only set, not clear restrictions */
	if ((nocell_new - nocell_old) == 0 &&
	    (noexpensive_new - noexpensive_old) == 0)
		return (0);
#if INET6
	if (SOCK_DOM(so) == PF_INET || SOCK_DOM(so) == PF_INET6) {
#else
	if (SOCK_DOM(so) == PF_INET) {
#endif /* !INET6 */
		if (nocell_new - nocell_old != 0) {
			/*
			 * if deny cellular is now set, do what's needed
			 * for INPCB
			 */
			inp_set_nocellular(sotoinpcb(so));
		}
		if (noexpensive_new - noexpensive_old != 0) {
			inp_set_noexpensive(sotoinpcb(so));
		}
	}

	if (SOCK_DOM(so) == PF_MULTIPATH)
		mptcp_set_restrictions(so);

	return (0);
}