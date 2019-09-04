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
struct ip6_moptions {int /*<<< orphan*/  im6o_trace; int /*<<< orphan*/  im6o_debug; int /*<<< orphan*/  im6o_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFD_ALLOC ; 
 int /*<<< orphan*/  IFD_DEBUG ; 
 int /*<<< orphan*/  IM6O_ADDREF (struct ip6_moptions*) ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct ip6_moptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifa_mtx_attr ; 
 int /*<<< orphan*/  ifa_mtx_grp ; 
 scalar_t__ im6o_debug ; 
 int /*<<< orphan*/  im6o_size ; 
 int /*<<< orphan*/  im6o_trace ; 
 int /*<<< orphan*/  im6o_zone ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip6_moptions* zalloc (int /*<<< orphan*/ ) ; 
 struct ip6_moptions* zalloc_noblock (int /*<<< orphan*/ ) ; 

struct ip6_moptions *
ip6_allocmoptions(int how)
{
	struct ip6_moptions *im6o;

	im6o = (how == M_WAITOK) ?
	    zalloc(im6o_zone) : zalloc_noblock(im6o_zone);
	if (im6o != NULL) {
		bzero(im6o, im6o_size);
		lck_mtx_init(&im6o->im6o_lock, ifa_mtx_grp, ifa_mtx_attr);
		im6o->im6o_debug |= IFD_ALLOC;
		if (im6o_debug != 0) {
			im6o->im6o_debug |= IFD_DEBUG;
			im6o->im6o_trace = im6o_trace;
		}
		IM6O_ADDREF(im6o);
	}

	return (im6o);
}