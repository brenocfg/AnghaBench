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
struct scope6_id {int* s6id_list; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IN6_IFEXTRA (struct ifnet*) ; 
#define  IPV6_ADDR_SCOPE_LINKLOCAL 131 
#define  IPV6_ADDR_SCOPE_NODELOCAL 130 
#define  IPV6_ADDR_SCOPE_ORGLOCAL 129 
#define  IPV6_ADDR_SCOPE_SITELOCAL 128 
 struct scope6_id* SID (struct ifnet*) ; 
 int /*<<< orphan*/  if_inet6data_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  if_inet6data_lock_shared (struct ifnet*) ; 
 int in6_addrscope (struct in6_addr*) ; 

int
in6_addr2scopeid(struct ifnet *ifp, struct in6_addr *addr)
{
	int scope = in6_addrscope(addr);
	int retid = 0;
	struct scope6_id *sid;

	if_inet6data_lock_shared(ifp);
	if (IN6_IFEXTRA(ifp) == NULL)
		goto err;
	sid = SID(ifp);
	switch (scope) {
	case IPV6_ADDR_SCOPE_NODELOCAL:
		retid = -1;	/* XXX: is this an appropriate value? */
		break;
	case IPV6_ADDR_SCOPE_LINKLOCAL:
		retid = sid->s6id_list[IPV6_ADDR_SCOPE_LINKLOCAL];
		break;
	case IPV6_ADDR_SCOPE_SITELOCAL:
		retid = sid->s6id_list[IPV6_ADDR_SCOPE_SITELOCAL];
		break;
	case IPV6_ADDR_SCOPE_ORGLOCAL:
		retid = sid->s6id_list[IPV6_ADDR_SCOPE_ORGLOCAL];
		break;
	default:
		break;	/* XXX: value 0, treat as global. */
	}
err:
	if_inet6data_lock_done(ifp);

	return (retid);
}