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
typedef  int u_long ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_family; } ;
struct in6_aliasreq {TYPE_2__ ifra_dstaddr; TYPE_1__ ifra_addr; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
#define  SIOCLL_START_32 129 
#define  SIOCLL_START_64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 struct in6_aliasreq* in6_aliasreq_to_native (int /*<<< orphan*/ ,int,struct in6_aliasreq*) ; 
 int /*<<< orphan*/  in6_if_up_dad_start (struct ifnet*) ; 
 int in6_ifattach_aliasreq (struct ifnet*,int /*<<< orphan*/ *,struct in6_aliasreq*) ; 

__attribute__((used)) static __attribute__((noinline)) int
in6ctl_llstart(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct in6_aliasreq sifra, *ifra = NULL;
	boolean_t is64;
	int error = 0;

	VERIFY(ifp != NULL);

	switch (cmd) {
	case SIOCLL_START_32:		/* struct in6_aliasreq_32 */
	case SIOCLL_START_64:		/* struct in6_aliasreq_64 */
		is64 = (cmd == SIOCLL_START_64);
		/*
		 * Convert user ifra to the kernel form, when appropriate.
		 * This allows the conversion between different data models
		 * to be centralized, so that it can be passed around to other
		 * routines that are expecting the kernel form.
		 */
		ifra = in6_aliasreq_to_native(data, is64, &sifra);

		/*
		 * NOTE: All the interface specific DLIL attachements should
		 * be done here.  They are currently done in in6_ifattach_aux()
		 * for the interfaces that need it.
		 */
		if (ifra->ifra_addr.sin6_family == AF_INET6 &&
		    /* Only check ifra_dstaddr if valid */
		    (ifra->ifra_dstaddr.sin6_len == 0 ||
		    ifra->ifra_dstaddr.sin6_family == AF_INET6)) {
		    /* some interfaces may provide LinkLocal addresses */
			error = in6_ifattach_aliasreq(ifp, NULL, ifra);
		} else {
			error = in6_ifattach_aliasreq(ifp, NULL, NULL);
		}
		if (error == 0)
			in6_if_up_dad_start(ifp);
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}