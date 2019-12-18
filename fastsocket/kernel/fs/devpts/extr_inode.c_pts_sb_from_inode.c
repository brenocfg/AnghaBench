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
struct super_block {scalar_t__ s_magic; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {struct super_block* mnt_sb; } ;

/* Variables and functions */
 scalar_t__ DEVPTS_SUPER_MAGIC ; 
 TYPE_1__* devpts_mnt ; 

__attribute__((used)) static inline struct super_block *pts_sb_from_inode(struct inode *inode)
{
#ifdef CONFIG_DEVPTS_MULTIPLE_INSTANCES
	if (inode->i_sb->s_magic == DEVPTS_SUPER_MAGIC)
		return inode->i_sb;
#endif
	return devpts_mnt->mnt_sb;
}