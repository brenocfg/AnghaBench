#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct vxfs_inode_info {int /*<<< orphan*/  vii_gen; int /*<<< orphan*/  vii_blocks; int /*<<< orphan*/  vii_mtime; int /*<<< orphan*/  vii_ctime; int /*<<< orphan*/  vii_atime; int /*<<< orphan*/  vii_size; int /*<<< orphan*/  vii_nlink; scalar_t__ vii_gid; scalar_t__ vii_uid; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {struct vxfs_inode_info* i_private; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_blocks; TYPE_3__ i_mtime; TYPE_2__ i_ctime; TYPE_1__ i_atime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; scalar_t__ i_gid; scalar_t__ i_uid; int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  vxfs_transmod (struct vxfs_inode_info*) ; 

__attribute__((used)) static void
vxfs_iinit(struct inode *ip, struct vxfs_inode_info *vip)
{

	ip->i_mode = vxfs_transmod(vip);
	ip->i_uid = (uid_t)vip->vii_uid;
	ip->i_gid = (gid_t)vip->vii_gid;

	ip->i_nlink = vip->vii_nlink;
	ip->i_size = vip->vii_size;

	ip->i_atime.tv_sec = vip->vii_atime;
	ip->i_ctime.tv_sec = vip->vii_ctime;
	ip->i_mtime.tv_sec = vip->vii_mtime;
	ip->i_atime.tv_nsec = 0;
	ip->i_ctime.tv_nsec = 0;
	ip->i_mtime.tv_nsec = 0;

	ip->i_blocks = vip->vii_blocks;
	ip->i_generation = vip->vii_gen;

	ip->i_private = vip;
	
}