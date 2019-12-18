#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct as_data {void** last_check_fifo; long* fifo_expire; TYPE_1__* fifo_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 void* jiffies ; 
 scalar_t__ list_empty (TYPE_1__*) ; 
 struct request* rq_entry_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_fifo_time (struct request*) ; 
 int time_after (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int as_fifo_expired(struct as_data *ad, int adir)
{
	struct request *rq;
	long delta_jif;

	delta_jif = jiffies - ad->last_check_fifo[adir];
	if (unlikely(delta_jif < 0))
		delta_jif = -delta_jif;
	if (delta_jif < ad->fifo_expire[adir])
		return 0;

	ad->last_check_fifo[adir] = jiffies;

	if (list_empty(&ad->fifo_list[adir]))
		return 0;

	rq = rq_entry_fifo(ad->fifo_list[adir].next);

	return time_after(jiffies, rq_fifo_time(rq));
}