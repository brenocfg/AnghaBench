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
struct vnop_remove_args {struct componentname* a_cnp; struct vnode* a_dvp; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct componentname {char* cn_nameptr; int cn_namelen; int cn_flags; } ;
struct TYPE_5__ {scalar_t__ dn_type; int dn_links; } ;
typedef  TYPE_1__ devnode_t ;
typedef  int /*<<< orphan*/  devdirent_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int DEVFS_UPDATE_CHANGE ; 
 int DEVFS_UPDATE_MOD ; 
 scalar_t__ DEV_DIR ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int ISDOTDOT ; 
 TYPE_1__* VTODN (struct vnode*) ; 
 int /*<<< orphan*/ * dev_findname (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_free_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfs_consider_time_update (TYPE_1__*,int) ; 
 scalar_t__ devfs_is_name_protected (struct vnode*,char*) ; 

__attribute__((used)) static int
devfs_vnop_remove(struct vnop_remove_args *ap)
        /* struct vnop_remove_args  {
                struct vnode *a_dvp;
                struct vnode *a_vp;
                struct componentname *a_cnp;
        } */ 
{
	struct vnode *vp = ap->a_vp;
	struct vnode *dvp = ap->a_dvp;
	struct componentname *cnp = ap->a_cnp;
	devnode_t *  tp;
	devnode_t *  tdp;
	devdirent_t * tnp;
	int doingdirectory = 0;
	int error = 0;

	/*
	 * assume that the name is null terminated as they
	 * are the end of the path. Get pointers to all our
	 * devfs structures.
	 */

	DEVFS_LOCK();

	tp = VTODN(vp);
	tdp = VTODN(dvp);


	tnp = dev_findname(tdp, cnp->cn_nameptr);

	if (tnp == NULL) {
	        error = ENOENT;
		goto abort;
	}

	/*
	 * Don't allow removing critical devfs devices
	 */
	if (devfs_is_name_protected(dvp, cnp->cn_nameptr)) {
		error = EINVAL;
		goto abort;
}

	/*
	 * Make sure that we don't try do something stupid
	 */
	if ((tp->dn_type) == DEV_DIR) {
		/*
		 * Avoid ".", "..", and aliases of "." for obvious reasons.
		 */
		if ( (cnp->cn_namelen == 1 && cnp->cn_nameptr[0] == '.') 
		    || (cnp->cn_flags&ISDOTDOT) ) {
			error = EINVAL;
			goto abort;
		}
		doingdirectory++;
	}

	/***********************************
	 * Start actually doing things.... *
	 ***********************************/
	devfs_consider_time_update(tdp, DEVFS_UPDATE_CHANGE | DEVFS_UPDATE_MOD);

	/*
	 * Target must be empty if a directory and have no links
	 * to it. Also, ensure source and target are compatible
	 * (both directories, or both not directories).
	 */
	if (( doingdirectory) && (tp->dn_links > 2)) {
	    error = ENOTEMPTY;
	    goto abort;
	}
	dev_free_name(tnp);
abort:
	DEVFS_UNLOCK();

	return (error);
}