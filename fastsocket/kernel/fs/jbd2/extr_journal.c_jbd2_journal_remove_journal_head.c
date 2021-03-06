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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __journal_remove_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_journal_head (struct buffer_head*) ; 

void jbd2_journal_remove_journal_head(struct buffer_head *bh)
{
	jbd_lock_bh_journal_head(bh);
	__journal_remove_journal_head(bh);
	jbd_unlock_bh_journal_head(bh);
}