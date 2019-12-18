#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vxfs_sb_info {TYPE_1__* vsi_raw; } ;
struct kstatfs {int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_ffree; scalar_t__ f_files; scalar_t__ f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {TYPE_2__* d_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_3__ {int /*<<< orphan*/  vs_ifree; int /*<<< orphan*/  vs_free; int /*<<< orphan*/  vs_dsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXFS_NAMELEN ; 
 struct vxfs_sb_info* VXFS_SBI (TYPE_2__*) ; 
 int /*<<< orphan*/  VXFS_SUPER_MAGIC ; 

__attribute__((used)) static int
vxfs_statfs(struct dentry *dentry, struct kstatfs *bufp)
{
	struct vxfs_sb_info		*infp = VXFS_SBI(dentry->d_sb);

	bufp->f_type = VXFS_SUPER_MAGIC;
	bufp->f_bsize = dentry->d_sb->s_blocksize;
	bufp->f_blocks = infp->vsi_raw->vs_dsize;
	bufp->f_bfree = infp->vsi_raw->vs_free;
	bufp->f_bavail = 0;
	bufp->f_files = 0;
	bufp->f_ffree = infp->vsi_raw->vs_ifree;
	bufp->f_namelen = VXFS_NAMELEN;

	return 0;
}