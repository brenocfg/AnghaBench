#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int sa_len; } ;
struct rtentry {struct ifnet* rt_ifp; } ;
struct TYPE_8__ {struct rtentry* ro_rt; } ;
struct inpcb {int inp_flags; int /*<<< orphan*/  inp_socket; TYPE_3__ in6p_route; int /*<<< orphan*/  in6p_outputopts; TYPE_1__* inp_boundifp; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_7__ {scalar_t__ sin6_family; scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {unsigned int if_index; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EADDRNOTAVAIL ; 
 int EAFNOSUPPORT ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 unsigned int IFSCOPE_NONE ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int INP_BOUND_IF ; 
 TYPE_2__* SIN6 (struct sockaddr*) ; 
 int SO_FILT_HINT_IFDENIED ; 
 int SO_FILT_HINT_LOCKED ; 
 int /*<<< orphan*/  ifnet_reference (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_release (struct ifnet*) ; 
 scalar_t__ in6_embedscope (int /*<<< orphan*/ *,TYPE_2__*,struct inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ in6_ifaddrs ; 
 struct in6_addr* in6_selectsrc (TYPE_2__*,int /*<<< orphan*/ ,struct inpcb*,TYPE_3__*,struct ifnet**,struct in6_addr*,unsigned int,int*) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 scalar_t__ inp_restricted_send (struct inpcb*,struct ifnet*) ; 
 int /*<<< orphan*/  soevent (int /*<<< orphan*/ ,int) ; 

int
in6_pcbladdr(struct inpcb *inp, struct sockaddr *nam,
    struct in6_addr *plocal_addr6, struct ifnet **outif)
{
	struct in6_addr *addr6 = NULL;
	struct in6_addr src_storage;
	int error = 0;
	unsigned int ifscope;

	if (outif != NULL)
		*outif = NULL;
	if (nam->sa_len != sizeof (struct sockaddr_in6))
		return (EINVAL);
	if (SIN6(nam)->sin6_family != AF_INET6)
		return (EAFNOSUPPORT);
	if (SIN6(nam)->sin6_port == 0)
		return (EADDRNOTAVAIL);

	/* KAME hack: embed scopeid */
	if (in6_embedscope(&SIN6(nam)->sin6_addr, SIN6(nam), inp, NULL, NULL) != 0)
		return (EINVAL);

	if (in6_ifaddrs) {
		/*
		 * If the destination address is UNSPECIFIED addr,
		 * use the loopback addr, e.g ::1.
		 */
		if (IN6_IS_ADDR_UNSPECIFIED(&SIN6(nam)->sin6_addr))
			SIN6(nam)->sin6_addr = in6addr_loopback;
	}

	ifscope = (inp->inp_flags & INP_BOUND_IF) ?
	    inp->inp_boundifp->if_index : IFSCOPE_NONE;

	/*
	 * XXX: in6_selectsrc might replace the bound local address
	 * with the address specified by setsockopt(IPV6_PKTINFO).
	 * Is it the intended behavior?
	 *
	 * in6_selectsrc() might return outif with its reference held
	 * even in the error case; caller always needs to release it
	 * if non-NULL.
	 */
	addr6 = in6_selectsrc(SIN6(nam), inp->in6p_outputopts, inp,
	    &inp->in6p_route, outif, &src_storage, ifscope, &error);

	if (outif != NULL) {
		struct rtentry *rt = inp->in6p_route.ro_rt;
		/*
		 * If in6_selectsrc() returns a route, it should be one
		 * which points to the same ifp as outif.  Just in case
		 * it isn't, use the one from the route for consistency.
		 * Otherwise if there is no route, leave outif alone as
		 * it could still be useful to the caller.
		 */
		if (rt != NULL && rt->rt_ifp != *outif) {
			ifnet_reference(rt->rt_ifp);	/* for caller */
			if (*outif != NULL)
				ifnet_release(*outif);
			*outif = rt->rt_ifp;
		}
	}

	if (addr6 == NULL) {
		if (outif != NULL && (*outif) != NULL &&
		    inp_restricted_send(inp, *outif)) {
			soevent(inp->inp_socket,
			    (SO_FILT_HINT_LOCKED | SO_FILT_HINT_IFDENIED));
			error = EHOSTUNREACH;
		}
		if (error == 0)
			error = EADDRNOTAVAIL;
		return (error);
	}

	*plocal_addr6 = *addr6;
	/*
	 * Don't do pcblookup call here; return interface in
	 * plocal_addr6 and exit to caller, that will do the lookup.
	 */
	return (0);
}