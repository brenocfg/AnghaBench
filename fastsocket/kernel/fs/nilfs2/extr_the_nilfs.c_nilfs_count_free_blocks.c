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
struct the_nilfs {int ns_blocks_per_segment; int /*<<< orphan*/  ns_sufile; } ;
struct inode {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 struct inode* nilfs_dat_inode (struct the_nilfs*) ; 
 int nilfs_sufile_get_ncleansegs (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_count_free_blocks(struct the_nilfs *nilfs, sector_t *nblocks)
{
	struct inode *dat = nilfs_dat_inode(nilfs);
	unsigned long ncleansegs;
	int err;

	down_read(&NILFS_MDT(dat)->mi_sem);	/* XXX */
	err = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile, &ncleansegs);
	up_read(&NILFS_MDT(dat)->mi_sem);	/* XXX */
	if (likely(!err))
		*nblocks = (sector_t)ncleansegs * nilfs->ns_blocks_per_segment;
	return err;
}