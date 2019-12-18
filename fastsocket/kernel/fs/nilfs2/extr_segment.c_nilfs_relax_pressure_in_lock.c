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
struct the_nilfs {int /*<<< orphan*/  ns_segctor_sem; } ;
struct super_block {int dummy; } ;
struct nilfs_transaction_info {int /*<<< orphan*/  ti_flags; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_flags; scalar_t__ sc_flush_request; } ;
struct nilfs_sb_info {struct the_nilfs* s_nilfs; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 struct nilfs_sc_info* NILFS_SC (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  NILFS_SC_PRIOR_FLUSH ; 
 int /*<<< orphan*/  NILFS_TI_WRITER ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segctor_do_immediate_flush (struct nilfs_sc_info*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void nilfs_relax_pressure_in_lock(struct super_block *sb)
{
	struct nilfs_sb_info *sbi = NILFS_SB(sb);
	struct nilfs_sc_info *sci = NILFS_SC(sbi);
	struct the_nilfs *nilfs = sbi->s_nilfs;

	if (!sci || !sci->sc_flush_request)
		return;

	set_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags);
	up_read(&nilfs->ns_segctor_sem);

	down_write(&nilfs->ns_segctor_sem);
	if (sci->sc_flush_request &&
	    test_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags)) {
		struct nilfs_transaction_info *ti = current->journal_info;

		ti->ti_flags |= NILFS_TI_WRITER;
		nilfs_segctor_do_immediate_flush(sci);
		ti->ti_flags &= ~NILFS_TI_WRITER;
	}
	downgrade_write(&nilfs->ns_segctor_sem);
}