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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_sb_info {int /*<<< orphan*/ * id_table; } ;
typedef  int /*<<< orphan*/  disk_id ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int SQUASHFS_ID_BLOCK (unsigned int) ; 
 int SQUASHFS_ID_BLOCK_OFFSET (unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int squashfs_read_metadata (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

int squashfs_get_id(struct super_block *sb, unsigned int index,
					unsigned int *id)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	int block = SQUASHFS_ID_BLOCK(index);
	int offset = SQUASHFS_ID_BLOCK_OFFSET(index);
	u64 start_block = le64_to_cpu(msblk->id_table[block]);
	__le32 disk_id;
	int err;

	err = squashfs_read_metadata(sb, &disk_id, &start_block, &offset,
							sizeof(disk_id));
	if (err < 0)
		return err;

	*id = le32_to_cpu(disk_id);
	return 0;
}