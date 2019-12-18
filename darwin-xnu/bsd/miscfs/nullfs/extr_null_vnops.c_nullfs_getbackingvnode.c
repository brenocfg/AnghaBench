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
typedef  int /*<<< orphan*/ * vnode_t ;
struct vfsstatfs {int /*<<< orphan*/  f_fstypename; } ;
typedef  int /*<<< orphan*/  mount_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/ * NULLVP ; 
 int /*<<< orphan*/  NULLVPTOLOWERVID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NULLVPTOLOWERVP (int /*<<< orphan*/ *) ; 
 scalar_t__ nullfs_checkspecialvp (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct vfsstatfs* vfs_statfs (int /*<<< orphan*/ ) ; 
 int vnode_getwithvid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ *) ; 

int
nullfs_getbackingvnode(vnode_t in_vp, vnode_t* out_vpp)
{
	int result = EINVAL;

	if (out_vpp == NULL || in_vp == NULL) {
		goto end;
	}

	struct vfsstatfs * sp   = NULL;
	mount_t mp = vnode_mount(in_vp);

	sp = vfs_statfs(mp);
	//If this isn't a nullfs vnode or it is but it's a special vnode
	if (strcmp(sp->f_fstypename, "nullfs") != 0 || nullfs_checkspecialvp(in_vp)) {
		*out_vpp = NULLVP;
		result = ENOENT;
		goto end;
	}

	vnode_t lvp = NULLVPTOLOWERVP(in_vp);
	if ((result = vnode_getwithvid(lvp, NULLVPTOLOWERVID(in_vp)))) {
		goto end;
	}

	*out_vpp = lvp;

end:
	return result;
}