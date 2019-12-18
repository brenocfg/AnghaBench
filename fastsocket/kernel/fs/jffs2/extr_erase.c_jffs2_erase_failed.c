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
typedef  scalar_t__ uint32_t ;
struct jffs2_sb_info {int /*<<< orphan*/  erase_wait; int /*<<< orphan*/  erase_free_sem; int /*<<< orphan*/  erase_completion_lock; int /*<<< orphan*/  nr_erasing_blocks; int /*<<< orphan*/  bad_list; scalar_t__ sector_size; int /*<<< orphan*/  bad_size; int /*<<< orphan*/  erasing_size; int /*<<< orphan*/  dirty_size; int /*<<< orphan*/  erase_pending_list; } ;
struct jffs2_eraseblock {int /*<<< orphan*/  list; scalar_t__ dirty_size; } ;

/* Variables and functions */
 scalar_t__ MTD_FAIL_ADDR_UNKNOWN ; 
 scalar_t__ jffs2_cleanmarker_oob (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_write_nand_badblock (struct jffs2_sb_info*,struct jffs2_eraseblock*,scalar_t__) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jffs2_erase_failed(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb, uint32_t bad_offset)
{
	/* For NAND, if the failure did not occur at the device level for a
	   specific physical page, don't bother updating the bad block table. */
	if (jffs2_cleanmarker_oob(c) && (bad_offset != (uint32_t)MTD_FAIL_ADDR_UNKNOWN)) {
		/* We had a device-level failure to erase.  Let's see if we've
		   failed too many times. */
		if (!jffs2_write_nand_badblock(c, jeb, bad_offset)) {
			/* We'd like to give this block another try. */
			mutex_lock(&c->erase_free_sem);
			spin_lock(&c->erase_completion_lock);
			list_move(&jeb->list, &c->erase_pending_list);
			c->erasing_size -= c->sector_size;
			c->dirty_size += c->sector_size;
			jeb->dirty_size = c->sector_size;
			spin_unlock(&c->erase_completion_lock);
			mutex_unlock(&c->erase_free_sem);
			return;
		}
	}

	mutex_lock(&c->erase_free_sem);
	spin_lock(&c->erase_completion_lock);
	c->erasing_size -= c->sector_size;
	c->bad_size += c->sector_size;
	list_move(&jeb->list, &c->bad_list);
	c->nr_erasing_blocks--;
	spin_unlock(&c->erase_completion_lock);
	mutex_unlock(&c->erase_free_sem);
	wake_up(&c->erase_wait);
}