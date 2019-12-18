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
struct rtentry {int dummy; } ;
struct TYPE_4__ {struct rtentry* ro_rt; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct inpcb {TYPE_2__ inp_route; TYPE_1__ inp_laddr; } ;
struct in_ifaddr {int /*<<< orphan*/  ia_ifa; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IFA_REMREF (int /*<<< orphan*/ *) ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  ROUTE_RELEASE (TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 struct in_ifaddr* ifa_foraddr (scalar_t__) ; 

void
in_rtchange(struct inpcb *inp, int errno)
{
#pragma unused(errno)
	boolean_t release = FALSE;
	struct rtentry *rt;

	if ((rt = inp->inp_route.ro_rt) != NULL) {
		struct in_ifaddr *ia = NULL;

		/* if address is gone, keep the old route */
		if (inp->inp_laddr.s_addr != INADDR_ANY &&
		    (ia = ifa_foraddr(inp->inp_laddr.s_addr)) != NULL) {
			/*
			 * Address is around; ditch the route.  A new route
			 * can be allocated the next time output is attempted.
			 */
			release = TRUE;
		}
		if (ia != NULL)
			IFA_REMREF(&ia->ia_ifa);
	}
	if (rt == NULL || release)
		ROUTE_RELEASE(&inp->inp_route);
}