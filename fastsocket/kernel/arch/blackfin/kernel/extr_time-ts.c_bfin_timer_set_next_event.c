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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSYNC () ; 
 int TMPWR ; 
 int TMREN ; 
 int /*<<< orphan*/  bfin_write_TCNTL (int) ; 
 int /*<<< orphan*/  bfin_write_TCOUNT (unsigned long) ; 

__attribute__((used)) static int bfin_timer_set_next_event(unsigned long cycles,
				struct clock_event_device *evt)
{
	bfin_write_TCNTL(TMPWR);
	CSYNC();
	bfin_write_TCOUNT(cycles);
	CSYNC();
	bfin_write_TCNTL(TMPWR | TMREN);
	return 0;
}