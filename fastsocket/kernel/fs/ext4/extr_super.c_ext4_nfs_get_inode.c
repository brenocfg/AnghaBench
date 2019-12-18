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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_generation; } ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_inodes_count; } ;

/* Variables and functions */
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ EXT4_FIRST_INO (struct super_block*) ; 
 scalar_t__ EXT4_ROOT_INO ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* ext4_iget (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *ext4_nfs_get_inode(struct super_block *sb,
					u64 ino, u32 generation)
{
	struct inode *inode;

	if (ino < EXT4_FIRST_INO(sb) && ino != EXT4_ROOT_INO)
		return ERR_PTR(-ESTALE);
	if (ino > le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count))
		return ERR_PTR(-ESTALE);

	/* iget isn't really right if the inode is currently unallocated!!
	 *
	 * ext4_read_inode will return a bad_inode if the inode had been
	 * deleted, so we should be safe.
	 *
	 * Currently we don't know the generation for parent directory, so
	 * a generation of 0 means "accept any"
	 */
	inode = ext4_iget(sb, ino);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (generation && inode->i_generation != generation) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}

	return inode;
}