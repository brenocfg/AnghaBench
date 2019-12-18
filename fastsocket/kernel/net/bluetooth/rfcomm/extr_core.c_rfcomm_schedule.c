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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  RFCOMM_SCHED_WAKEUP ; 
 int /*<<< orphan*/  rfcomm_event ; 
 int /*<<< orphan*/  rfcomm_thread ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rfcomm_schedule(uint event)
{
	if (!rfcomm_thread)
		return;
	//set_bit(event, &rfcomm_event);
	set_bit(RFCOMM_SCHED_WAKEUP, &rfcomm_event);
	wake_up_process(rfcomm_thread);
}