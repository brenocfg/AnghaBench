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
struct journal_head {struct jbd2_buffer_trigger_type* b_triggers; } ;
struct jbd2_buffer_trigger_type {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct journal_head* bh2jh (struct buffer_head*) ; 

void jbd2_journal_set_triggers(struct buffer_head *bh,
			       struct jbd2_buffer_trigger_type *type)
{
	struct journal_head *jh = bh2jh(bh);

	jh->b_triggers = type;
}