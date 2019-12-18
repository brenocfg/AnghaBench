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
struct TYPE_2__ {int /*<<< orphan*/ * priv_root; int /*<<< orphan*/ * xattr_root; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  d_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 

__attribute__((used)) static void reiserfs_kill_sb(struct super_block *s)
{
	if (REISERFS_SB(s)) {
		if (REISERFS_SB(s)->xattr_root) {
			d_invalidate(REISERFS_SB(s)->xattr_root);
			dput(REISERFS_SB(s)->xattr_root);
			REISERFS_SB(s)->xattr_root = NULL;
		}
		if (REISERFS_SB(s)->priv_root) {
			d_invalidate(REISERFS_SB(s)->priv_root);
			dput(REISERFS_SB(s)->priv_root);
			REISERFS_SB(s)->priv_root = NULL;
		}
	}

	kill_block_super(s);
}