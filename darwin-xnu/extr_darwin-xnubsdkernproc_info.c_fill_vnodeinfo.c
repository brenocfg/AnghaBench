#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_8__ {scalar_t__* val; } ;
struct vnode_info {int /*<<< orphan*/  vi_type; TYPE_2__ vi_fsid; int /*<<< orphan*/  vi_stat; } ;
struct stat64 {int dummy; } ;
struct TYPE_7__ {TYPE_2__ f_fsid; } ;
struct TYPE_10__ {TYPE_1__ mnt_vfsstat; } ;
struct TYPE_9__ {int /*<<< orphan*/  v_type; TYPE_6__* v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct stat64*,int) ; 
 TYPE_6__* dead_mountp ; 
 int /*<<< orphan*/  munge_vinfo_stat (struct stat64*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_rele (int /*<<< orphan*/ ) ; 
 int vn_stat (TYPE_3__*,struct stat64*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
fill_vnodeinfo(vnode_t vp, struct vnode_info *vinfo)
{
		vfs_context_t context;
		struct stat64 sb;
		int error = 0;

		bzero(&sb, sizeof(struct stat64));
		context = vfs_context_create((vfs_context_t)0);
		error = vn_stat(vp, &sb, NULL, 1, context);
		(void)vfs_context_rele(context);

		munge_vinfo_stat(&sb, &vinfo->vi_stat);

		if (error != 0)
			goto out;

		if (vp->v_mount != dead_mountp) {
			vinfo->vi_fsid = vp->v_mount->mnt_vfsstat.f_fsid;
		} else {
			vinfo->vi_fsid.val[0] = 0;
			vinfo->vi_fsid.val[1] = 0;
		}
		vinfo->vi_type = vp->v_type;
out:
		return(error);
}