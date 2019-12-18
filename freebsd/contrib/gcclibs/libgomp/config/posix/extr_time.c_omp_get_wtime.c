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
struct timeval {double tv_sec; int tv_usec; } ;
struct timespec {double tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

double
omp_get_wtime (void)
{
#ifdef HAVE_CLOCK_GETTIME
  struct timespec ts;
# ifdef CLOCK_MONOTONIC
  if (clock_gettime (CLOCK_MONOTONIC, &ts) < 0)
# endif
    clock_gettime (CLOCK_REALTIME, &ts);
  return ts.tv_sec + ts.tv_nsec / 1e9;
#else
  struct timeval tv;
  gettimeofday (&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1e6;
#endif
}