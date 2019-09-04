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
typedef  int u_long ;
struct in6_cgareq {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
#define  SIOCLL_CGASTART_32 129 
#define  SIOCLL_CGASTART_64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_cgareq_to_native (int /*<<< orphan*/ ,int,struct in6_cgareq*) ; 
 int /*<<< orphan*/  in6_if_up_dad_start (struct ifnet*) ; 
 int in6_ifattach_llcgareq (struct ifnet*,struct in6_cgareq*) ; 

__attribute__((used)) static __attribute__((noinline)) int
in6ctl_cgastart(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct in6_cgareq llcgasr;
	int is64, error = 0;

	VERIFY(ifp != NULL);

	switch (cmd) {
	case SIOCLL_CGASTART_32:	/* struct in6_cgareq_32 */
	case SIOCLL_CGASTART_64:	/* struct in6_cgareq_64 */
		is64 = (cmd == SIOCLL_CGASTART_64);
		/*
		 * Convert user cgareq to the kernel form, when appropriate.
		 * This allows the conversion between different data models
		 * to be centralized, so that it can be passed around to other
		 * routines that are expecting the kernel form.
		 */
		in6_cgareq_to_native(data, is64, &llcgasr);

		/*
		 * NOTE: All the interface specific DLIL attachements
		 * should be done here.  They are currently done in
		 * in6_ifattach_cgareq() for the interfaces that
		 * need it.
		 */
		error = in6_ifattach_llcgareq(ifp, &llcgasr);
		if (error == 0)
			in6_if_up_dad_start(ifp);
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}