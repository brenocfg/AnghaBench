#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct componentname {int cn_namelen; char* cn_nameptr; int cn_flags; int /*<<< orphan*/  cn_hash; } ;
struct TYPE_8__ {scalar_t__ v_parent; int v_flag; int v_nc_generation; int /*<<< orphan*/  v_nclinks; int /*<<< orphan*/ * v_name; } ;

/* Variables and functions */
 int ISDOTDOT ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int MAKEENTRY ; 
 scalar_t__ NULLVP ; 
 int VNCACHEABLE ; 
 int VNODE_UPDATE_NAME ; 
 int VNODE_UPDATE_PARENT ; 
 int /*<<< orphan*/  cache_enter_with_gen (TYPE_1__*,TYPE_1__*,struct componentname*,int) ; 
 int /*<<< orphan*/  vnode_update_identity (TYPE_1__*,TYPE_1__*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void 
lookup_consider_update_cache(vnode_t dvp, vnode_t vp, struct componentname *cnp, int nc_generation) 
{
	int isdot_or_dotdot;
	isdot_or_dotdot = (cnp->cn_namelen == 1 && cnp->cn_nameptr[0] == '.') || (cnp->cn_flags & ISDOTDOT);

	if (vp->v_name == NULL || vp->v_parent == NULLVP) {
		int  update_flags = 0;

		if (isdot_or_dotdot == 0) {
			if (vp->v_name == NULL)
				update_flags |= VNODE_UPDATE_NAME;
			if (dvp != NULLVP && vp->v_parent == NULLVP)
				update_flags |= VNODE_UPDATE_PARENT;

			if (update_flags)
				vnode_update_identity(vp, dvp, cnp->cn_nameptr, cnp->cn_namelen, cnp->cn_hash, update_flags);
		}
	}
	if ( (cnp->cn_flags & MAKEENTRY) && (vp->v_flag & VNCACHEABLE) && LIST_FIRST(&vp->v_nclinks) == NULL) {
		/*
		 * missing from name cache, but should
		 * be in it... this can happen if volfs
		 * causes the vnode to be created or the
		 * name cache entry got recycled but the
		 * vnode didn't...
		 * check to make sure that ni_dvp is valid
		 * cache_lookup_path may return a NULL
		 * do a quick check to see if the generation of the
		 * directory matches our snapshot... this will get
		 * rechecked behind the name cache lock, but if it
		 * already fails to match, no need to go any further
		 */
		if (dvp != NULLVP && (nc_generation == dvp->v_nc_generation) && (!isdot_or_dotdot))
			cache_enter_with_gen(dvp, vp, cnp, nc_generation);
	}

}