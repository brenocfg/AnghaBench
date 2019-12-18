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
struct ext3_dir_entry_2 {int /*<<< orphan*/  inode; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_error (int /*<<< orphan*/ ,char*,char*,unsigned long) ; 
 struct buffer_head* ext3_find_entry (TYPE_1__*,struct qstr*,struct ext3_dir_entry_2**) ; 
 int /*<<< orphan*/  ext3_iget (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ext3_valid_inum (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

struct dentry *ext3_get_parent(struct dentry *child)
{
	unsigned long ino;
	struct qstr dotdot = {.name = "..", .len = 2};
	struct ext3_dir_entry_2 * de;
	struct buffer_head *bh;

	bh = ext3_find_entry(child->d_inode, &dotdot, &de);
	if (!bh)
		return ERR_PTR(-ENOENT);
	ino = le32_to_cpu(de->inode);
	brelse(bh);

	if (!ext3_valid_inum(child->d_inode->i_sb, ino)) {
		ext3_error(child->d_inode->i_sb, "ext3_get_parent",
			   "bad inode number: %lu", ino);
		return ERR_PTR(-EIO);
	}

	return d_obtain_alias(ext3_iget(child->d_inode->i_sb, ino));
}