#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nilfs_transaction_info {int /*<<< orphan*/  ti_flags; int /*<<< orphan*/  ti_garbage; int /*<<< orphan*/  ti_magic; struct nilfs_transaction_info* ti_save; scalar_t__ ti_count; } ;
struct nilfs_sb_info {TYPE_1__* s_nilfs; } ;
struct TYPE_7__ {struct nilfs_transaction_info* journal_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  sc_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  ns_segctor_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* NILFS_SC (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  NILFS_SC_PRIOR_FLUSH ; 
 int /*<<< orphan*/  NILFS_TI_GC ; 
 int /*<<< orphan*/  NILFS_TI_MAGIC ; 
 int /*<<< orphan*/  NILFS_TI_WRITER ; 
 int /*<<< orphan*/  WARN_ON (struct nilfs_transaction_info*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segctor_do_immediate_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static void nilfs_transaction_lock(struct nilfs_sb_info *sbi,
				   struct nilfs_transaction_info *ti,
				   int gcflag)
{
	struct nilfs_transaction_info *cur_ti = current->journal_info;

	WARN_ON(cur_ti);
	ti->ti_flags = NILFS_TI_WRITER;
	ti->ti_count = 0;
	ti->ti_save = cur_ti;
	ti->ti_magic = NILFS_TI_MAGIC;
	INIT_LIST_HEAD(&ti->ti_garbage);
	current->journal_info = ti;

	for (;;) {
		down_write(&sbi->s_nilfs->ns_segctor_sem);
		if (!test_bit(NILFS_SC_PRIOR_FLUSH, &NILFS_SC(sbi)->sc_flags))
			break;

		nilfs_segctor_do_immediate_flush(NILFS_SC(sbi));

		up_write(&sbi->s_nilfs->ns_segctor_sem);
		yield();
	}
	if (gcflag)
		ti->ti_flags |= NILFS_TI_GC;
}