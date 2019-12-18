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
struct nd_defrouter {int /*<<< orphan*/  nddr_trace; int /*<<< orphan*/  nddr_debug; int /*<<< orphan*/  nddr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ALLOC ; 
 int /*<<< orphan*/  IFD_DEBUG ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_mtx_attr ; 
 int /*<<< orphan*/  ifa_mtx_grp ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nddr_debug ; 
 int /*<<< orphan*/  nddr_size ; 
 int /*<<< orphan*/  nddr_trace ; 
 int /*<<< orphan*/  nddr_zone ; 
 struct nd_defrouter* zalloc (int /*<<< orphan*/ ) ; 
 struct nd_defrouter* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nd_defrouter *
nddr_alloc(int how)
{
	struct nd_defrouter *dr;

	dr = (how == M_WAITOK) ? zalloc(nddr_zone) : zalloc_noblock(nddr_zone);
	if (dr != NULL) {
		bzero(dr, nddr_size);
		lck_mtx_init(&dr->nddr_lock, ifa_mtx_grp, ifa_mtx_attr);
		dr->nddr_debug |= IFD_ALLOC;
		if (nddr_debug != 0) {
			dr->nddr_debug |= IFD_DEBUG;
			dr->nddr_trace = nddr_trace;
		}
	}
	return (dr);
}