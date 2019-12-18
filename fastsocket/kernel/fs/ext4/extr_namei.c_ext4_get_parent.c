#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qstr {char* name; int len; } ;
struct inode {int dummy; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  inode; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct buffer_head* ext4_find_entry (TYPE_1__*,struct qstr const*,struct ext4_dir_entry_2**) ; 
 int /*<<< orphan*/  ext4_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_valid_inum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

struct dentry *ext4_get_parent(struct dentry *child)
{
	__u32 ino;
	struct inode *inode;
	static const struct qstr dotdot = {
		.name = "..",
		.len = 2,
	};
	struct ext4_dir_entry_2 * de;
	struct buffer_head *bh;

	bh = ext4_find_entry(child->d_inode, &dotdot, &de);
	inode = NULL;
	if (!bh)
		return ERR_PTR(-ENOENT);
	ino = le32_to_cpu(de->inode);
	brelse(bh);

	if (!ext4_valid_inum(child->d_inode->i_sb, ino)) {
		ext4_error(child->d_inode->i_sb,
			   "bad inode number: %u", ino);
		return ERR_PTR(-EIO);
	}

	return d_obtain_alias(ext4_iget(child->d_inode->i_sb, ino));
}