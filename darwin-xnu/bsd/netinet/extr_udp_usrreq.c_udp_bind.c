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
struct socket {int /*<<< orphan*/  last_pid; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct proc {int dummy; } ;
struct inpcb {int inp_flags2; int /*<<< orphan*/  necp_client_uuid; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int INP2_CONNECT_IN_PROGRESS ; 
 int in_pcbbind (struct inpcb*,struct sockaddr*,struct proc*) ; 
 int /*<<< orphan*/  necp_client_assign_from_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inpcb*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

int
udp_bind(struct socket *so, struct sockaddr *nam, struct proc *p)
{
	struct inpcb *inp;
	int error;

	if (nam->sa_family != 0 && nam->sa_family != AF_INET &&
	    nam->sa_family != AF_INET6)
		return (EAFNOSUPPORT);

	inp = sotoinpcb(so);
	if (inp == NULL)
		return (EINVAL);
	error = in_pcbbind(inp, nam, p);

#if NECP
	/* Update NECP client with bind result if not in middle of connect */
	if (error == 0 &&
		(inp->inp_flags2 & INP2_CONNECT_IN_PROGRESS) &&
		!uuid_is_null(inp->necp_client_uuid)) {
		socket_unlock(so, 0);
		necp_client_assign_from_socket(so->last_pid, inp->necp_client_uuid, inp);
		socket_lock(so, 0);
	}
#endif /* NECP */

	return (error);
}