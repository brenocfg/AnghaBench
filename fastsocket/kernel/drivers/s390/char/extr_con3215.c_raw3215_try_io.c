#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct raw3215_info {int flags; TYPE_2__ timer; TYPE_1__* queued_write; int /*<<< orphan*/ * queued_read; } ;
struct TYPE_5__ {scalar_t__ delayable; } ;

/* Variables and functions */
 int RAW3215_ACTIVE ; 
 int RAW3215_FLUSHING ; 
 int RAW3215_FROZEN ; 
 scalar_t__ RAW3215_TIMEOUT ; 
 int RAW3215_TIMER_RUNS ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  raw3215_start_io (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_timeout ; 

__attribute__((used)) static inline void raw3215_try_io(struct raw3215_info *raw)
{
	if (!(raw->flags & RAW3215_ACTIVE) || (raw->flags & RAW3215_FROZEN))
		return;
	if (raw->queued_read != NULL)
		raw3215_start_io(raw);
	else if (raw->queued_write != NULL) {
		if ((raw->queued_write->delayable == 0) ||
		    (raw->flags & RAW3215_FLUSHING)) {
			/* execute write requests bigger than minimum size */
			raw3215_start_io(raw);
			if (raw->flags & RAW3215_TIMER_RUNS) {
				del_timer(&raw->timer);
				raw->flags &= ~RAW3215_TIMER_RUNS;
			}
		} else if (!(raw->flags & RAW3215_TIMER_RUNS)) {
			/* delay small writes */
			init_timer(&raw->timer);
			raw->timer.expires = RAW3215_TIMEOUT + jiffies;
			raw->timer.data = (unsigned long) raw;
			raw->timer.function = raw3215_timeout;
			add_timer(&raw->timer);
			raw->flags |= RAW3215_TIMER_RUNS;
		}
	}
}