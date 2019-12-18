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
typedef  scalar_t__ time_t ;
struct timeval {int /*<<< orphan*/  tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
gettimeofday (struct timeval *tp, void *tz)
{
  if (tz)
    abort ();
  tp->tv_usec = 0;
  if (time (&tp->tv_sec) == (time_t) -1)
    return -1;
  return 0;
}