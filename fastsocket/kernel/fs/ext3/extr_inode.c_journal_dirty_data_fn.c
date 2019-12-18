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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int ext3_journal_dirty_data (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int journal_dirty_data_fn(handle_t *handle, struct buffer_head *bh)
{
	/*
	 * Write could have mapped the buffer but it didn't copy the data in
	 * yet. So avoid filing such buffer into a transaction.
	 */
	if (buffer_mapped(bh) && buffer_uptodate(bh))
		return ext3_journal_dirty_data(handle, bh);
	return 0;
}