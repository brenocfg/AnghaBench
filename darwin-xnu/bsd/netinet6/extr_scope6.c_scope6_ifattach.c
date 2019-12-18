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
struct ifnet {int if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IN6_IFEXTRA (struct ifnet*) ; 
 size_t IPV6_ADDR_SCOPE_INTFACELOCAL ; 
 size_t IPV6_ADDR_SCOPE_LINKLOCAL ; 
 size_t IPV6_ADDR_SCOPE_ORGLOCAL ; 
 size_t IPV6_ADDR_SCOPE_SITELOCAL ; 
 struct scope6_id* SID (struct ifnet*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inet6data_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  if_inet6data_lock_exclusive (struct ifnet*) ; 

void
scope6_ifattach(struct ifnet *ifp)
{
	struct scope6_id *sid;

	VERIFY(IN6_IFEXTRA(ifp) != NULL);
	if_inet6data_lock_exclusive(ifp);
	sid = SID(ifp);
	/* N.B.: the structure is already zero'ed */
	/*
	 * XXX: IPV6_ADDR_SCOPE_xxx macros are not standard.
	 * Should we rather hardcode here?
	 */
	sid->s6id_list[IPV6_ADDR_SCOPE_INTFACELOCAL] = ifp->if_index;
	sid->s6id_list[IPV6_ADDR_SCOPE_LINKLOCAL] = ifp->if_index;
#if MULTI_SCOPE
	/* by default, we don't care about scope boundary for these scopes. */
	sid->s6id_list[IPV6_ADDR_SCOPE_SITELOCAL] = 1;
	sid->s6id_list[IPV6_ADDR_SCOPE_ORGLOCAL] = 1;
#endif
	if_inet6data_lock_done(ifp);
}