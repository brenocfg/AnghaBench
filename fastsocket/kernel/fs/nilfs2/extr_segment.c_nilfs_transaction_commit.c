#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nilfs_transaction_info {scalar_t__ ti_magic; int ti_flags; scalar_t__ ti_count; struct nilfs_transaction_info* ti_save; } ;
struct nilfs_sc_info {scalar_t__ sc_watermark; } ;
struct nilfs_sb_info {TYPE_1__* s_nilfs; } ;
struct TYPE_4__ {struct nilfs_transaction_info* journal_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  ns_segctor_sem; int /*<<< orphan*/  ns_ndirtyblks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 struct nilfs_sc_info* NILFS_SC (struct nilfs_sb_info*) ; 
 int NILFS_TI_COMMIT ; 
 int NILFS_TI_DYNAMIC_ALLOC ; 
 scalar_t__ NILFS_TI_MAGIC ; 
 int NILFS_TI_SYNC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nilfs_transaction_info*) ; 
 int nilfs_construct_segment (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_segctor_do_flush (struct nilfs_sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_segctor_start_timer (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  nilfs_transaction_cachep ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_transaction_commit(struct super_block *sb)
{
	struct nilfs_transaction_info *ti = current->journal_info;
	struct nilfs_sb_info *sbi;
	struct nilfs_sc_info *sci;
	int err = 0;

	BUG_ON(ti == NULL || ti->ti_magic != NILFS_TI_MAGIC);
	ti->ti_flags |= NILFS_TI_COMMIT;
	if (ti->ti_count > 0) {
		ti->ti_count--;
		return 0;
	}
	sbi = NILFS_SB(sb);
	sci = NILFS_SC(sbi);
	if (sci != NULL) {
		if (ti->ti_flags & NILFS_TI_COMMIT)
			nilfs_segctor_start_timer(sci);
		if (atomic_read(&sbi->s_nilfs->ns_ndirtyblks) >
		    sci->sc_watermark)
			nilfs_segctor_do_flush(sci, 0);
	}
	up_read(&sbi->s_nilfs->ns_segctor_sem);
	current->journal_info = ti->ti_save;

	if (ti->ti_flags & NILFS_TI_SYNC)
		err = nilfs_construct_segment(sb);
	if (ti->ti_flags & NILFS_TI_DYNAMIC_ALLOC)
		kmem_cache_free(nilfs_transaction_cachep, ti);
	return err;
}