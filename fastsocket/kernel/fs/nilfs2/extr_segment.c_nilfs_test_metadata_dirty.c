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
struct the_nilfs {int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_cpfile; } ;
struct nilfs_sb_info {int /*<<< orphan*/  s_ifile; struct the_nilfs* s_nilfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_dat_inode (struct the_nilfs*) ; 
 scalar_t__ nilfs_doing_gc () ; 
 scalar_t__ nilfs_mdt_fetch_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_test_metadata_dirty(struct nilfs_sb_info *sbi)
{
	struct the_nilfs *nilfs = sbi->s_nilfs;
	int ret = 0;

	if (nilfs_mdt_fetch_dirty(sbi->s_ifile))
		ret++;
	if (nilfs_mdt_fetch_dirty(nilfs->ns_cpfile))
		ret++;
	if (nilfs_mdt_fetch_dirty(nilfs->ns_sufile))
		ret++;
	if (ret || nilfs_doing_gc())
		if (nilfs_mdt_fetch_dirty(nilfs_dat_inode(nilfs)))
			ret++;
	return ret;
}