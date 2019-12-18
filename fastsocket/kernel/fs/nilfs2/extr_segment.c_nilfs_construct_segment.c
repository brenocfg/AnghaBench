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
struct nilfs_transaction_info {scalar_t__ ti_magic; } ;
struct nilfs_sc_info {int dummy; } ;
struct nilfs_sb_info {int dummy; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EROFS ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 struct nilfs_sc_info* NILFS_SC (struct nilfs_sb_info*) ; 
 scalar_t__ NILFS_TI_MAGIC ; 
 TYPE_1__* current ; 
 int nilfs_segctor_sync (struct nilfs_sc_info*) ; 

int nilfs_construct_segment(struct super_block *sb)
{
	struct nilfs_sb_info *sbi = NILFS_SB(sb);
	struct nilfs_sc_info *sci = NILFS_SC(sbi);
	struct nilfs_transaction_info *ti;
	int err;

	if (!sci)
		return -EROFS;

	/* A call inside transactions causes a deadlock. */
	BUG_ON((ti = current->journal_info) && ti->ti_magic == NILFS_TI_MAGIC);

	err = nilfs_segctor_sync(sci);
	return err;
}