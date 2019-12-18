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
struct dm_table {int /*<<< orphan*/  event_context; int /*<<< orphan*/  (* event_fn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _event_lock ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void dm_table_event(struct dm_table *t)
{
	/*
	 * You can no longer call dm_table_event() from interrupt
	 * context, use a bottom half instead.
	 */
	BUG_ON(in_interrupt());

	mutex_lock(&_event_lock);
	if (t->event_fn)
		t->event_fn(t->event_context);
	mutex_unlock(&_event_lock);
}