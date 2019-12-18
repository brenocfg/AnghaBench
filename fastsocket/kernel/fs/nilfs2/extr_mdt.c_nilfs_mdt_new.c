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
struct the_nilfs {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_MDT_GFP ; 
 int /*<<< orphan*/  def_mdt_aops ; 
 int /*<<< orphan*/  def_mdt_fops ; 
 int /*<<< orphan*/  def_mdt_iops ; 
 struct inode* nilfs_mdt_new_common (struct the_nilfs*,struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct inode *nilfs_mdt_new(struct the_nilfs *nilfs, struct super_block *sb,
			    ino_t ino)
{
	struct inode *inode = nilfs_mdt_new_common(nilfs, sb, ino,
						   NILFS_MDT_GFP);

	if (!inode)
		return NULL;

	inode->i_op = &def_mdt_iops;
	inode->i_fop = &def_mdt_fops;
	inode->i_mapping->a_ops = &def_mdt_aops;
	return inode;
}