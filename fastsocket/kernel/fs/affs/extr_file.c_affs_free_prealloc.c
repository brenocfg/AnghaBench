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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_lastalloc; scalar_t__ i_pa_cnt; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  affs_free_block (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void
affs_free_prealloc(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;

	pr_debug("AFFS: free_prealloc(ino=%lu)\n", inode->i_ino);

	while (AFFS_I(inode)->i_pa_cnt) {
		AFFS_I(inode)->i_pa_cnt--;
		affs_free_block(sb, ++AFFS_I(inode)->i_lastalloc);
	}
}