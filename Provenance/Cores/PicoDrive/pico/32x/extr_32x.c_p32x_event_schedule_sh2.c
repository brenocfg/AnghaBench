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
typedef  enum p32x_event { ____Placeholder_p32x_event } p32x_event ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 unsigned int event_time_next ; 
 int /*<<< orphan*/  p32x_event_schedule (unsigned int,int,int) ; 
 unsigned int sh2_cycles_done_m68k (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh2_end_run (int /*<<< orphan*/ *,int) ; 

void p32x_event_schedule_sh2(SH2 *sh2, enum p32x_event event, int after)
{
  unsigned int now = sh2_cycles_done_m68k(sh2);
  int left_to_next;

  p32x_event_schedule(now, event, after);

  left_to_next = (event_time_next - now) * 3;
  sh2_end_run(sh2, left_to_next);
}