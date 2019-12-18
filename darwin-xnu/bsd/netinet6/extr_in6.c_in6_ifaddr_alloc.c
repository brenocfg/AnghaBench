#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in6_ifaddr_dbg {int /*<<< orphan*/  in6ifa_alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifa_detached; int /*<<< orphan*/  ifa_attached; int /*<<< orphan*/  ifa_trace; int /*<<< orphan*/  ifa_debug; int /*<<< orphan*/  ifa_free; } ;
struct in6_ifaddr {TYPE_1__ ia_ifa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ALLOC ; 
 int /*<<< orphan*/  IFD_DEBUG ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct in6_ifaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrace_record (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifa_lock_init (TYPE_1__*) ; 
 int /*<<< orphan*/  in6_ifaddr_attached ; 
 int /*<<< orphan*/  in6_ifaddr_detached ; 
 int /*<<< orphan*/  in6_ifaddr_free ; 
 int /*<<< orphan*/  in6_ifaddr_trace ; 
 scalar_t__ in6ifa_debug ; 
 int /*<<< orphan*/  in6ifa_size ; 
 int /*<<< orphan*/  in6ifa_zone ; 
 struct in6_ifaddr* zalloc (int /*<<< orphan*/ ) ; 
 struct in6_ifaddr* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct in6_ifaddr *
in6_ifaddr_alloc(int how)
{
	struct in6_ifaddr *in6ifa;

	in6ifa = (how == M_WAITOK) ? zalloc(in6ifa_zone) :
	    zalloc_noblock(in6ifa_zone);
	if (in6ifa != NULL) {
		bzero(in6ifa, in6ifa_size);
		in6ifa->ia_ifa.ifa_free = in6_ifaddr_free;
		in6ifa->ia_ifa.ifa_debug |= IFD_ALLOC;
		ifa_lock_init(&in6ifa->ia_ifa);
		if (in6ifa_debug != 0) {
			struct in6_ifaddr_dbg *in6ifa_dbg =
			    (struct in6_ifaddr_dbg *)in6ifa;
			in6ifa->ia_ifa.ifa_debug |= IFD_DEBUG;
			in6ifa->ia_ifa.ifa_trace = in6_ifaddr_trace;
			in6ifa->ia_ifa.ifa_attached = in6_ifaddr_attached;
			in6ifa->ia_ifa.ifa_detached = in6_ifaddr_detached;
			ctrace_record(&in6ifa_dbg->in6ifa_alloc);
		}
	}

	return (in6ifa);
}