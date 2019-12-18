#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sl; scalar_t__ es; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETR_EVENT_SWITCH_LOCAL ; 
 int /*<<< orphan*/  disable_sync_clock (int /*<<< orphan*/ *) ; 
 TYPE_1__ etr_eacr ; 
 int /*<<< orphan*/  etr_events ; 
 int /*<<< orphan*/  etr_setr (TYPE_1__*) ; 
 int /*<<< orphan*/  etr_work ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_sync_wq ; 

void etr_switch_to_local(void)
{
	if (!etr_eacr.sl)
		return;
	disable_sync_clock(NULL);
	if (!test_and_set_bit(ETR_EVENT_SWITCH_LOCAL, &etr_events)) {
		etr_eacr.es = etr_eacr.sl = 0;
		etr_setr(&etr_eacr);
		queue_work(time_sync_wq, &etr_work);
	}
}