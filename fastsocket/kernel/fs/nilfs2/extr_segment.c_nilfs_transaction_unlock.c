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
struct nilfs_transaction_info {scalar_t__ ti_magic; scalar_t__ ti_count; int /*<<< orphan*/  ti_garbage; struct nilfs_transaction_info* ti_save; } ;
struct nilfs_sb_info {TYPE_1__* s_nilfs; } ;
struct TYPE_4__ {struct nilfs_transaction_info* journal_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  ns_segctor_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NILFS_TI_MAGIC ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_dispose_list (struct nilfs_sb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_transaction_unlock(struct nilfs_sb_info *sbi)
{
	struct nilfs_transaction_info *ti = current->journal_info;

	BUG_ON(ti == NULL || ti->ti_magic != NILFS_TI_MAGIC);
	BUG_ON(ti->ti_count > 0);

	up_write(&sbi->s_nilfs->ns_segctor_sem);
	current->journal_info = ti->ti_save;
	if (!list_empty(&ti->ti_garbage))
		nilfs_dispose_list(sbi, &ti->ti_garbage, 0);
}