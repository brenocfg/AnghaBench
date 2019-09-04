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
typedef  int u_int32_t ;
struct scope6_id {int* s6id_list; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr16; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/ * IN6_IFEXTRA (struct ifnet*) ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr*) ; 
 scalar_t__ IN6_IS_ADDR_MC_INTFACELOCAL (struct in6_addr*) ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (struct in6_addr*) ; 
#define  IPV6_ADDR_SCOPE_INTFACELOCAL 131 
#define  IPV6_ADDR_SCOPE_LINKLOCAL 130 
#define  IPV6_ADDR_SCOPE_ORGLOCAL 129 
#define  IPV6_ADDR_SCOPE_SITELOCAL 128 
 struct scope6_id* SID (struct ifnet*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  if_inet6data_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  if_inet6data_lock_shared (struct ifnet*) ; 
 int in6_addrscope (struct in6_addr*) ; 

int
in6_setscope(struct in6_addr *in6, struct ifnet *ifp, u_int32_t *ret_id)
{
	int scope;
	u_int32_t zoneid = 0;
	struct scope6_id *sid;

	/*
	 * special case: the loopback address can only belong to a loopback
	 * interface.
	 */
	if (IN6_IS_ADDR_LOOPBACK(in6)) {
		if (!(ifp->if_flags & IFF_LOOPBACK)) {
			return (EINVAL);
		} else {
			if (ret_id != NULL)
				*ret_id = 0; /* there's no ambiguity */
			return (0);
		}
	}

	scope = in6_addrscope(in6);

	if_inet6data_lock_shared(ifp);
	if (IN6_IFEXTRA(ifp) == NULL) {
		if_inet6data_lock_done(ifp);
		if (ret_id)
			*ret_id = 0;
		return (EINVAL);
	}
	sid = SID(ifp);
	switch (scope) {
	case IPV6_ADDR_SCOPE_INTFACELOCAL: /* should be interface index */
		zoneid = sid->s6id_list[IPV6_ADDR_SCOPE_INTFACELOCAL];
		break;

	case IPV6_ADDR_SCOPE_LINKLOCAL:
		zoneid = sid->s6id_list[IPV6_ADDR_SCOPE_LINKLOCAL];
		break;

	case IPV6_ADDR_SCOPE_SITELOCAL:
		zoneid = sid->s6id_list[IPV6_ADDR_SCOPE_SITELOCAL];
		break;

	case IPV6_ADDR_SCOPE_ORGLOCAL:
		zoneid = sid->s6id_list[IPV6_ADDR_SCOPE_ORGLOCAL];
		break;
	default:
		zoneid = 0;	/* XXX: treat as global. */
		break;
	}
	if_inet6data_lock_done(ifp);

	if (ret_id != NULL)
		*ret_id = zoneid;

	if (IN6_IS_SCOPE_LINKLOCAL(in6) || IN6_IS_ADDR_MC_INTFACELOCAL(in6))
		in6->s6_addr16[1] = htons(zoneid & 0xffff); /* XXX */

	return (0);
}