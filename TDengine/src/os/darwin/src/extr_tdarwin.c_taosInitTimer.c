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
struct TYPE_2__ {int tv_usec; scalar_t__ tv_sec; } ;
struct itimerval {TYPE_1__ it_interval; TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 

int taosInitTimer(void (*callback)(int), int ms) {
  signal(SIGALRM, callback);

  struct itimerval tv;
  tv.it_interval.tv_sec = 0;  /* my timer resolution */
  tv.it_interval.tv_usec = 1000 * ms;  // resolution is in msecond
  tv.it_value = tv.it_interval;

  return setitimer(ITIMER_REAL, &tv, NULL);
}