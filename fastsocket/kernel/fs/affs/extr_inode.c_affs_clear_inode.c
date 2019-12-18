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
struct inode {int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int i_ext_last; int /*<<< orphan*/ * i_ext_bh; int /*<<< orphan*/ * i_ac; int /*<<< orphan*/ * i_lc; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  affs_brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  affs_free_prealloc (struct inode*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

void
affs_clear_inode(struct inode *inode)
{
	unsigned long cache_page;

	pr_debug("AFFS: clear_inode(ino=%lu, nlink=%u)\n", inode->i_ino, inode->i_nlink);

	affs_free_prealloc(inode);
	cache_page = (unsigned long)AFFS_I(inode)->i_lc;
	if (cache_page) {
		pr_debug("AFFS: freeing ext cache\n");
		AFFS_I(inode)->i_lc = NULL;
		AFFS_I(inode)->i_ac = NULL;
		free_page(cache_page);
	}
	affs_brelse(AFFS_I(inode)->i_ext_bh);
	AFFS_I(inode)->i_ext_last = ~1;
	AFFS_I(inode)->i_ext_bh = NULL;
}