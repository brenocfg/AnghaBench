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
struct nilfs_sc_info {int /*<<< orphan*/  sc_flags; struct nilfs_sb_info* sc_sbi; } ;
struct nilfs_sb_info {int /*<<< orphan*/  s_inode_lock; int /*<<< orphan*/  s_dirty_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SC_DIRTY ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ nilfs_segctor_clean (struct nilfs_sc_info*) ; 
 scalar_t__ nilfs_test_metadata_dirty (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segctor_confirm(struct nilfs_sc_info *sci)
{
	struct nilfs_sb_info *sbi = sci->sc_sbi;
	int ret = 0;

	if (nilfs_test_metadata_dirty(sbi))
		set_bit(NILFS_SC_DIRTY, &sci->sc_flags);

	spin_lock(&sbi->s_inode_lock);
	if (list_empty(&sbi->s_dirty_files) && nilfs_segctor_clean(sci))
		ret++;

	spin_unlock(&sbi->s_inode_lock);
	return ret;
}