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
struct sockaddr_in6 {scalar_t__ sin6_family; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_port; scalar_t__ sin6_scope_id; scalar_t__ sin6_flowinfo; } ;
struct sockaddr {int sa_len; } ;
struct proc {int dummy; } ;
struct inpcb {struct ifnet* in6p_last_outifp; int /*<<< orphan*/  in6p_laddr; } ;
struct in6_ifaddr {int ia6_flags; } ;
struct ifnet {int dummy; } ;
struct ifaddr {struct ifnet* ifa_ifp; } ;
typedef  int /*<<< orphan*/  sin6 ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  IFA_LOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int IN6_IFF_ANYCAST ; 
 int IN6_IFF_CLAT46 ; 
 int IN6_IFF_DEPRECATED ; 
 int IN6_IFF_DETACHED ; 
 int IN6_IFF_NOTREADY ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA (struct sockaddr_in6*) ; 
 struct sockaddr_in6* SIN6 (struct sockaddr*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 struct ifaddr* ifa_ifwithaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_head ; 
 int /*<<< orphan*/  ip6_use_defzone ; 
 scalar_t__ necp_socket_should_use_flow_divert (struct inpcb*) ; 
 int sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip6_bind(struct socket *so, struct sockaddr *nam, struct proc *p)
{
#pragma unused(p)
	struct inpcb *inp = sotoinpcb(so);
	struct sockaddr_in6 sin6;
	struct ifaddr *ifa = NULL;
	struct ifnet *outif = NULL;
	int error;

	if (inp == NULL
#if NECP
		|| (necp_socket_should_use_flow_divert(inp))
#endif /* NECP */
		)
		return (inp == NULL ? EINVAL : EPROTOTYPE);

	if (nam->sa_len != sizeof (struct sockaddr_in6))
		return (EINVAL);

	if (TAILQ_EMPTY(&ifnet_head) || SIN6(nam)->sin6_family != AF_INET6)
		return (EADDRNOTAVAIL);

	bzero(&sin6, sizeof (sin6));
	*(&sin6) = *SIN6(nam);

	if ((error = sa6_embedscope(&sin6, ip6_use_defzone)) != 0)
		return (error);

	/* Sanitize local copy for address searches */
	sin6.sin6_flowinfo = 0;
	sin6.sin6_scope_id = 0;
	sin6.sin6_port = 0;

	if (!IN6_IS_ADDR_UNSPECIFIED(&sin6.sin6_addr) &&
	    (ifa = ifa_ifwithaddr(SA(&sin6))) == 0)
		return (EADDRNOTAVAIL);
	if (ifa != NULL) {
		IFA_LOCK(ifa);
		if (((struct in6_ifaddr *)ifa)->ia6_flags &
		    (IN6_IFF_ANYCAST | IN6_IFF_NOTREADY | IN6_IFF_CLAT46 |
		     IN6_IFF_DETACHED | IN6_IFF_DEPRECATED)) {
			IFA_UNLOCK(ifa);
			IFA_REMREF(ifa);
			return (EADDRNOTAVAIL);
		}
		outif = ifa->ifa_ifp;
		IFA_UNLOCK(ifa);
		IFA_REMREF(ifa);
	}
	inp->in6p_laddr = sin6.sin6_addr;
	inp->in6p_last_outifp = outif;

	return (0);
}