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
typedef  int ulonglong ;

/* Variables and functions */

__attribute__((used)) static void my_timer_init_overhead(ulonglong *overhead,
                                   ulonglong (*cycle_timer)(void),
                                   ulonglong (*this_timer)(void),
                                   ulonglong best_timer_overhead)
{
  ulonglong time1, time2;
  int i;

  /* *overhead, least of 20 calculations - cycles_overhead */
  for (i= 0, *overhead= 1000000000; i < 20; ++i)
  {
    time1= cycle_timer();
    this_timer(); /* rather than 'time_tmp= timer();' */
    time2= cycle_timer() - time1;
    if (*overhead > time2)
      *overhead= time2;
  }
  *overhead-= best_timer_overhead;
}