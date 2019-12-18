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
struct TYPE_4__ {int /*<<< orphan*/ * i1_data; } ;
struct minix_inode_info {TYPE_2__ u; } ;
struct minix_inode {int /*<<< orphan*/ * i_zone; int /*<<< orphan*/  i_time; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlinks; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; TYPE_1__ i_mtime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_high2lowgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_high2lowuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct minix_inode* minix_V1_raw_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 struct minix_inode_info* minix_i (struct inode*) ; 
 int /*<<< orphan*/  old_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buffer_head * V1_minix_update_inode(struct inode * inode)
{
	struct buffer_head * bh;
	struct minix_inode * raw_inode;
	struct minix_inode_info *minix_inode = minix_i(inode);
	int i;

	raw_inode = minix_V1_raw_inode(inode->i_sb, inode->i_ino, &bh);
	if (!raw_inode)
		return NULL;
	raw_inode->i_mode = inode->i_mode;
	raw_inode->i_uid = fs_high2lowuid(inode->i_uid);
	raw_inode->i_gid = fs_high2lowgid(inode->i_gid);
	raw_inode->i_nlinks = inode->i_nlink;
	raw_inode->i_size = inode->i_size;
	raw_inode->i_time = inode->i_mtime.tv_sec;
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		raw_inode->i_zone[0] = old_encode_dev(inode->i_rdev);
	else for (i = 0; i < 9; i++)
		raw_inode->i_zone[i] = minix_inode->u.i1_data[i];
	mark_buffer_dirty(bh);
	return bh;
}