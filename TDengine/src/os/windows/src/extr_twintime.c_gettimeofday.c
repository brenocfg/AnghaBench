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
typedef  scalar_t__ time_t ;
struct timezone {int dummy; } ;
struct timeval {long tv_sec; int tv_usec; } ;
struct TYPE_3__ {int wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int gettimeofday(struct timeval *tv, struct timezone *tz) {
  time_t t;
  t = time(NULL);
  SYSTEMTIME st;
  GetLocalTime(&st);

  tv->tv_sec = (long)t;
  tv->tv_usec = st.wMilliseconds * 1000;

  return 0;
}