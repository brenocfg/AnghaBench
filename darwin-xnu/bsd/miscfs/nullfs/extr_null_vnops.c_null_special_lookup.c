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
struct vnop_lookup_args {struct vnode** a_vpp; int /*<<< orphan*/  a_context; struct vnode* a_dvp; struct componentname* a_cnp; } ;
struct vnode {int dummy; } ;
struct null_mount {int nullm_flags; struct vnode* nullm_lowerrootvp; struct vnode* nullm_thirdcovervp; int /*<<< orphan*/  nullm_lowerrootvid; struct vnode* nullm_rootvp; struct vnode* nullm_secondvp; } ;
struct mount {int dummy; } ;
struct componentname {char* cn_nameptr; int cn_namelen; } ;

/* Variables and functions */
 int ENOENT ; 
 struct null_mount* MOUNTTONULLMOUNT (struct mount*) ; 
 int NULLM_CASEINSENSITIVE ; 
 int VNOP_LOOKUP (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int null_get_lowerparent (struct vnode*,struct vnode**,int /*<<< orphan*/ ) ; 
 int null_getnewvnode (struct mount*,int /*<<< orphan*/ *,struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int null_nodeget (struct mount*,struct vnode*,struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ) ; 
 int vnode_get (struct vnode*) ; 
 int vnode_getwithvid (struct vnode*,int /*<<< orphan*/ ) ; 
 struct mount* vnode_mount (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

__attribute__((used)) static int
null_special_lookup(struct vnop_lookup_args * ap)
{
	struct componentname * cnp  = ap->a_cnp;
	struct vnode * dvp          = ap->a_dvp;
	struct vnode * ldvp         = NULL;
	struct vnode * lvp          = NULL;
	struct vnode * vp           = NULL;
	struct mount * mp           = vnode_mount(dvp);
	struct null_mount * null_mp = MOUNTTONULLMOUNT(mp);
	int error                   = ENOENT;

	if (dvp == null_mp->nullm_rootvp) {
		/* handle . and .. */
		if (cnp->cn_nameptr[0] == '.') {
			if (cnp->cn_namelen == 1 || (cnp->cn_namelen == 2 && cnp->cn_nameptr[1] == '.')) {
				/* this is the root so both . and .. give back the root */
				vp    = dvp;
				error = vnode_get(vp);
				goto end;
			}
		}

		/* our virtual wrapper directory should be d but D is acceptable if the
		 * lower file system is case insensitive */
		if (cnp->cn_namelen == 1 &&
		    (cnp->cn_nameptr[0] == 'd' || (null_mp->nullm_flags & NULLM_CASEINSENSITIVE ? cnp->cn_nameptr[0] == 'D' : 0))) {
			error = 0;
			if (null_mp->nullm_secondvp == NULL) {
				error = null_getnewvnode(mp, NULL, dvp, &vp, cnp, 0);
				if (error) {
					goto end;
				}

				null_mp->nullm_secondvp = vp;
			} else {
				vp    = null_mp->nullm_secondvp;
				error = vnode_get(vp);
			}
		}

	} else if (dvp == null_mp->nullm_secondvp) {
		/* handle . and .. */
		if (cnp->cn_nameptr[0] == '.') {
			if (cnp->cn_namelen == 1) {
				vp    = dvp;
				error = vnode_get(vp);
				goto end;
			} else if (cnp->cn_namelen == 2 && cnp->cn_nameptr[1] == '.') {
				/* parent here is the root vp */
				vp    = null_mp->nullm_rootvp;
				error = vnode_get(vp);
				goto end;
			}
		}
		/* nullmp->nullm_lowerrootvp was set at mount time so don't need to lock to
		 * access it */
		/* v_name should be null terminated but cn_nameptr is not necessarily.
		   cn_namelen is the number of characters before the null in either case */
		error = vnode_getwithvid(null_mp->nullm_lowerrootvp, null_mp->nullm_lowerrootvid);
		if (error) {
			goto end;
		}

		/* We don't want to mess with case insensitivity and unicode, so the plan to
		   check here is
		    1. try to get the lower root's parent
		    2. If we get a parent, then perform a lookup on the lower file system
		   using the parent and the passed in cnp
		    3. If that worked and we got a vp, then see if the vp is lowerrootvp. If
		   so we got a match
		    4. Anything else results in ENOENT.
		    */
		error = null_get_lowerparent(null_mp->nullm_lowerrootvp, &ldvp, ap->a_context);

		if (error == 0) {
			error = VNOP_LOOKUP(ldvp, &lvp, cnp, ap->a_context);
			vnode_put(ldvp);

			if (error == 0) {
				if (lvp == null_mp->nullm_lowerrootvp) {
					/* always check the hashmap for a vnode for this, the root of the
					 * mirrored system */
					error = null_nodeget(mp, lvp, dvp, &vp, cnp, 0);

					if (error == 0 && null_mp->nullm_thirdcovervp == NULL) {
						/* if nodeget succeeded then vp has an iocount*/
						null_mp->nullm_thirdcovervp = vp;
					}
				} else {
					error = ENOENT;
				}
				vnode_put(lvp);
			}
		}
		vnode_put(null_mp->nullm_lowerrootvp);
	}

end:
	if (error == 0) {
		*ap->a_vpp = vp;
	}
	return error;
}