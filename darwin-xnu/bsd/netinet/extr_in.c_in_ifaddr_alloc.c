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
struct in_ifaddr_dbg {int /*<<< orphan*/  inifa_alloc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifa_detached; int /*<<< orphan*/  ifa_attached; int /*<<< orphan*/  ifa_trace; int /*<<< orphan*/  ifa_debug; int /*<<< orphan*/  ifa_free; } ;
struct in_ifaddr {TYPE_1__ ia_ifa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ALLOC ; 
 int /*<<< orphan*/  IFD_DEBUG ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct in_ifaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrace_record (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifa_lock_init (TYPE_1__*) ; 
 int /*<<< orphan*/  in_ifaddr_attached ; 
 int /*<<< orphan*/  in_ifaddr_detached ; 
 int /*<<< orphan*/  in_ifaddr_free ; 
 int /*<<< orphan*/  in_ifaddr_trace ; 
 scalar_t__ inifa_debug ; 
 int /*<<< orphan*/  inifa_size ; 
 int /*<<< orphan*/  inifa_zone ; 
 struct in_ifaddr* zalloc (int /*<<< orphan*/ ) ; 
 struct in_ifaddr* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct in_ifaddr *
in_ifaddr_alloc(int how)
{
	struct in_ifaddr *inifa;

	inifa = (how == M_WAITOK) ? zalloc(inifa_zone) :
	    zalloc_noblock(inifa_zone);
	if (inifa != NULL) {
		bzero(inifa, inifa_size);
		inifa->ia_ifa.ifa_free = in_ifaddr_free;
		inifa->ia_ifa.ifa_debug |= IFD_ALLOC;
		ifa_lock_init(&inifa->ia_ifa);
		if (inifa_debug != 0) {
			struct in_ifaddr_dbg *inifa_dbg =
			    (struct in_ifaddr_dbg *)inifa;
			inifa->ia_ifa.ifa_debug |= IFD_DEBUG;
			inifa->ia_ifa.ifa_trace = in_ifaddr_trace;
			inifa->ia_ifa.ifa_attached = in_ifaddr_attached;
			inifa->ia_ifa.ifa_detached = in_ifaddr_detached;
			ctrace_record(&inifa_dbg->inifa_alloc);
		}
	}
	return (inifa);
}