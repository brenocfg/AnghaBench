#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  TYPE_2__* mount_t ;
typedef  int boolean_t ;
struct TYPE_9__ {TYPE_1__* mnt_vnodecovered; } ;
struct TYPE_8__ {int v_flag; struct TYPE_8__* v_parent; TYPE_2__* v_mount; } ;

/* Variables and functions */
 int FALSE ; 
 TYPE_1__* NULLVP ; 
 int TRUE ; 
 int VISHARDLINK ; 
 int VROOT ; 
 TYPE_1__* rootvnode ; 

__attribute__((used)) static boolean_t
cache_check_vnode_issubdir(vnode_t vp, vnode_t dvp, boolean_t *is_subdir,
    vnode_t *next_vp)
{
	vnode_t tvp = vp;
	int defer = FALSE;

	*is_subdir = FALSE;
	*next_vp = NULLVP;
	while (1) {
		mount_t tmp;

		if (tvp == dvp) {
			*is_subdir = TRUE;
			break;
		} else if (tvp == rootvnode) {
			/* *is_subdir = FALSE */
			break;
		}

		tmp = tvp->v_mount;
		while ((tvp->v_flag & VROOT) && tmp && tmp->mnt_vnodecovered &&
		    tvp != dvp && tvp != rootvnode) {
			tvp = tmp->mnt_vnodecovered;
			tmp = tvp->v_mount;
		}

		/*
		 * If dvp is not at the top of a mount "stack" then
		 * vp is not a subdirectory of dvp either.
		 */
		if (tvp == dvp || tvp == rootvnode) {
			/* *is_subdir = FALSE */
			break;
		}

		if (!tmp) {
			defer = TRUE;
			*next_vp = NULLVP;
			break;
		}

		if ((tvp->v_flag & VISHARDLINK) || !(tvp->v_parent)) {
			defer = TRUE;
			*next_vp = tvp;
			break;
		}

		tvp = tvp->v_parent;
	}

	return (defer);
}