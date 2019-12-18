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
struct nilfs_inode_info {int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_flags; } ;
struct nilfs_inode {void* i_device_code; void* i_generation; void* i_flags; void* i_blocks; void* i_mtime_nsec; void* i_ctime_nsec; void* i_mtime; void* i_ctime; void* i_size; void* i_links_count; void* i_gid; void* i_uid; void* i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_blocks; TYPE_2__ i_mtime; TYPE_1__ i_ctime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_bmap_write (int /*<<< orphan*/ ,struct nilfs_inode*) ; 

void nilfs_write_inode_common(struct inode *inode,
			      struct nilfs_inode *raw_inode, int has_bmap)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);

	raw_inode->i_mode = cpu_to_le16(inode->i_mode);
	raw_inode->i_uid = cpu_to_le32(inode->i_uid);
	raw_inode->i_gid = cpu_to_le32(inode->i_gid);
	raw_inode->i_links_count = cpu_to_le16(inode->i_nlink);
	raw_inode->i_size = cpu_to_le64(inode->i_size);
	raw_inode->i_ctime = cpu_to_le64(inode->i_ctime.tv_sec);
	raw_inode->i_mtime = cpu_to_le64(inode->i_mtime.tv_sec);
	raw_inode->i_ctime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);
	raw_inode->i_mtime_nsec = cpu_to_le32(inode->i_mtime.tv_nsec);
	raw_inode->i_blocks = cpu_to_le64(inode->i_blocks);

	raw_inode->i_flags = cpu_to_le32(ii->i_flags);
	raw_inode->i_generation = cpu_to_le32(inode->i_generation);

	if (has_bmap)
		nilfs_bmap_write(ii->i_bmap, raw_inode);
	else if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		raw_inode->i_device_code =
			cpu_to_le64(new_encode_dev(inode->i_rdev));
	/* When extending inode, nilfs->ns_inode_size should be checked
	   for substitutions of appended fields */
}