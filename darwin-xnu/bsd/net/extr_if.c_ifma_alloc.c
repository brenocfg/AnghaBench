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
struct ifmultiaddr {int /*<<< orphan*/  ifma_trace; int /*<<< orphan*/  ifma_debug; int /*<<< orphan*/  ifma_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ALLOC ; 
 int /*<<< orphan*/  IFD_DEBUG ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct ifmultiaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_mtx_attr ; 
 int /*<<< orphan*/  ifa_mtx_grp ; 
 scalar_t__ ifma_debug ; 
 int /*<<< orphan*/  ifma_size ; 
 int /*<<< orphan*/  ifma_trace ; 
 int /*<<< orphan*/  ifma_zone ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifmultiaddr* zalloc (int /*<<< orphan*/ ) ; 
 struct ifmultiaddr* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ifmultiaddr *
ifma_alloc(int how)
{
	struct ifmultiaddr *ifma;

	ifma = (how == M_WAITOK) ? zalloc(ifma_zone) :
	    zalloc_noblock(ifma_zone);

	if (ifma != NULL) {
		bzero(ifma, ifma_size);
		lck_mtx_init(&ifma->ifma_lock, ifa_mtx_grp, ifa_mtx_attr);
		ifma->ifma_debug |= IFD_ALLOC;
		if (ifma_debug != 0) {
			ifma->ifma_debug |= IFD_DEBUG;
			ifma->ifma_trace = ifma_trace;
		}
	}
	return (ifma);
}