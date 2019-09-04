#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
struct TYPE_3__ {int cn_flags; } ;
struct nameidata {int ni_flag; TYPE_1__ ni_cnd; int /*<<< orphan*/  ni_ncgeneration; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_VNODE1 ; 
 int /*<<< orphan*/  ARG_VNODE2 ; 
 int AUDITVNPATH1 ; 
 int AUDITVNPATH2 ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int EKEEPLOOKING ; 
 int MAKEENTRY ; 
 int NAMEI_COMPOUND_OP_MASK ; 
 scalar_t__ NULLVP ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kdebug_lookup (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  lookup_consider_update_cache (scalar_t__,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnpath ; 

void
lookup_compound_vnop_post_hook(int error, vnode_t dvp, vnode_t vp, struct nameidata *ndp, int did_create)
{
	if (error == 0 && vp == NULLVP) {
		panic("NULL vp with error == 0.\n");
	}

	/* 
	 * We don't want to do any of this if we didn't use the compound vnop
	 * to perform the lookup... i.e. if we're allowing and using the legacy pattern,
	 * where we did a full lookup.
	 */
	if ((ndp->ni_flag & NAMEI_COMPOUND_OP_MASK) == 0) {
		return;
	}

	/* 
	 * If we're going to continue the lookup, we'll handle
	 * all lookup-related updates at that time.
	 */
	if (error == EKEEPLOOKING) {
		return;
	}

	/*
	 * Only audit or update cache for *found* vnodes.  For creation
	 * neither would happen in the non-compound-vnop case.
	 */
	if ((vp != NULLVP) && !did_create) {
		/* 
		 * If MAKEENTRY isn't set, and we've done a successful compound VNOP, 
		 * then we certainly don't want to update cache or identity.
		 */
		if ((error != 0) || (ndp->ni_cnd.cn_flags & MAKEENTRY)) {
			lookup_consider_update_cache(dvp, vp, &ndp->ni_cnd, ndp->ni_ncgeneration);
		}
		if (ndp->ni_cnd.cn_flags & AUDITVNPATH1)
			AUDIT_ARG(vnpath, vp, ARG_VNODE1);
		else if (ndp->ni_cnd.cn_flags & AUDITVNPATH2)
			AUDIT_ARG(vnpath, vp, ARG_VNODE2);
	}

	/* 
	 * If you created (whether you opened or not), cut a lookup tracepoint 
	 * for the parent dir (as would happen without a compound vnop).  Note: we may need
	 * a vnode despite failure in this case!
	 *
	 * If you did not create:
	 * 	Found child (succeeded or not): cut a tracepoint for the child.  
	 * 	Did not find child: cut a tracepoint with the parent.
	 */
	if (kdebug_enable) {
	        kdebug_lookup(vp ? vp : dvp, &ndp->ni_cnd); 
	}
}