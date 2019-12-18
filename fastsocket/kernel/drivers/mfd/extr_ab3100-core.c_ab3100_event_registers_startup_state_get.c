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
typedef  int /*<<< orphan*/  u32 ;
struct ab3100 {int /*<<< orphan*/  startup_events; int /*<<< orphan*/  startup_events_read; } ;

/* Variables and functions */
 int EAGAIN ; 

int ab3100_event_registers_startup_state_get(struct ab3100 *ab3100,
					     u32 *fatevent)
{
	if (!ab3100->startup_events_read)
		return -EAGAIN; /* Try again later */
	*fatevent = ab3100->startup_events;
	return 0;
}