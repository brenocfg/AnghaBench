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
struct the_nilfs {int dummy; } ;
struct nilfs_sb_info {int /*<<< orphan*/ * s_sc_info; struct the_nilfs* s_nilfs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NILFS_SC (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_attach_writer (struct the_nilfs*,struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  nilfs_detach_writer (struct the_nilfs*,struct nilfs_sb_info*) ; 
 int nilfs_segctor_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nilfs_segctor_new (struct nilfs_sb_info*) ; 

int nilfs_attach_segment_constructor(struct nilfs_sb_info *sbi)
{
	struct the_nilfs *nilfs = sbi->s_nilfs;
	int err;

	/* Each field of nilfs_segctor is cleared through the initialization
	   of super-block info */
	sbi->s_sc_info = nilfs_segctor_new(sbi);
	if (!sbi->s_sc_info)
		return -ENOMEM;

	nilfs_attach_writer(nilfs, sbi);
	err = nilfs_segctor_init(NILFS_SC(sbi));
	if (err) {
		nilfs_detach_writer(nilfs, sbi);
		kfree(sbi->s_sc_info);
		sbi->s_sc_info = NULL;
	}
	return err;
}