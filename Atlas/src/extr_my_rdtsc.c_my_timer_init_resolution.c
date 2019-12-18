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
 int MY_TIMER_ITERATIONS ; 

__attribute__((used)) static ulonglong my_timer_init_resolution(ulonglong (*this_timer)(void),
                                          ulonglong overhead_times_2)
{
  ulonglong time1, time2;
  ulonglong best_jump;
  int i, jumps, divisible_by_1000, divisible_by_1000000;

  divisible_by_1000= divisible_by_1000000= 0;
  best_jump= 1000000;
  for (i= jumps= 0; jumps < 3 && i < MY_TIMER_ITERATIONS * 10; ++i)
  {
    time1= this_timer();
    time2= this_timer();
    time2-= time1;
    if (time2)
    {
      ++jumps;
      if (!(time2 % 1000))
      {
        ++divisible_by_1000;
        if (!(time2 % 1000000))
          ++divisible_by_1000000;
      }
      if (best_jump > time2)
        best_jump= time2;
      /* For milliseconds, one jump is enough. */
      if (overhead_times_2 == 0)
        break;
    }
  }
  if (jumps == 3)
  {
    if (jumps == divisible_by_1000000)
      return 1000000;
    if (jumps == divisible_by_1000)
      return 1000;
  }
  if (best_jump > overhead_times_2)
    return best_jump;
  return 1;
}