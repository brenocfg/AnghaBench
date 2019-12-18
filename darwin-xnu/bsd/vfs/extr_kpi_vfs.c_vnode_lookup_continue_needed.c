#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct nameidata {int ni_flag; } ;
struct componentname {int cn_flags; struct nameidata* cn_ndp; } ;
struct TYPE_5__ {scalar_t__ v_resolve; int /*<<< orphan*/ * v_mountedhere; } ;

/* Variables and functions */
 int EKEEPLOOKING ; 
 int FOLLOW ; 
 int NAMEI_CONTLOOKUP ; 
 int NAMEI_TRAILINGSLASH ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vnode_isdir (TYPE_1__*) ; 
 scalar_t__ vnode_islnk (TYPE_1__*) ; 

int
vnode_lookup_continue_needed(vnode_t vp, struct componentname *cnp)
{
	struct nameidata *ndp = cnp->cn_ndp;

	if (ndp == NULL) {
		panic("vnode_lookup_continue_needed(): cnp->cn_ndp is NULL\n");
	}

	if (vnode_isdir(vp)) {
		if (vp->v_mountedhere != NULL) {
			goto yes;
		}

#if CONFIG_TRIGGERS
		if (vp->v_resolve) {
			goto yes;
		}
#endif /* CONFIG_TRIGGERS */

	}


	if (vnode_islnk(vp)) {
		/* From lookup():  || *ndp->ni_next == '/') No need for this, we know we're NULL-terminated here */
		if (cnp->cn_flags & FOLLOW) { 
			goto yes;
		}
		if (ndp->ni_flag & NAMEI_TRAILINGSLASH) {
			goto yes;
		}
	}

	return 0;

yes:
	ndp->ni_flag |= NAMEI_CONTLOOKUP;
	return EKEEPLOOKING;
}