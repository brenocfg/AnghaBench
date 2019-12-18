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
struct journal_head {int /*<<< orphan*/  b_jcount; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct journal_head* bh2jh (struct buffer_head*) ; 
 scalar_t__ buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_lock_bh_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_journal_head (struct buffer_head*) ; 

struct journal_head *journal_grab_journal_head(struct buffer_head *bh)
{
	struct journal_head *jh = NULL;

	jbd_lock_bh_journal_head(bh);
	if (buffer_jbd(bh)) {
		jh = bh2jh(bh);
		jh->b_jcount++;
	}
	jbd_unlock_bh_journal_head(bh);
	return jh;
}