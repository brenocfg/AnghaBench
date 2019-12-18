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
struct timespec {double tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  _SC_CLK_TCK ; 
 scalar_t__ clock_getres (int /*<<< orphan*/ ,struct timespec*) ; 
 double sysconf (int /*<<< orphan*/ ) ; 

double
omp_get_wtick (void)
{
#ifdef HAVE_CLOCK_GETTIME
  struct timespec ts;
# ifdef CLOCK_MONOTONIC
  if (clock_getres (CLOCK_MONOTONIC, &ts) < 0)
# endif
    clock_getres (CLOCK_REALTIME, &ts);
  return ts.tv_sec + ts.tv_nsec / 1e9;
#else
  return 1.0 / sysconf(_SC_CLK_TCK);
#endif
}