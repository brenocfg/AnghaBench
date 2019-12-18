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
struct buffer_head {int /*<<< orphan*/  b_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 

__attribute__((used)) static void journal_do_submit_data(struct buffer_head **wbuf, int bufs,
				   int write_op)
{
	int i;

	for (i = 0; i < bufs; i++) {
		wbuf[i]->b_end_io = end_buffer_write_sync;
		/* We use-up our safety reference in submit_bh() */
		submit_bh(write_op, wbuf[i]);
	}
}