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
struct timeval {unsigned long tv_usec; } ;
struct TYPE_3__ {unsigned long dwHighDateTime; unsigned long dwLowDateTime; } ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long
gather_time_entropy(void)
{
#ifdef _WIN32
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft); /* never fails */
  return ft.dwHighDateTime ^ ft.dwLowDateTime;
#else
  struct timeval tv;
  int gettimeofday_res;

  gettimeofday_res = gettimeofday(&tv, NULL);

#if defined(NDEBUG)
  (void)gettimeofday_res;
#else
  assert (gettimeofday_res == 0);
#endif  /* defined(NDEBUG) */

  /* Microseconds time is <20 bits entropy */
  return tv.tv_usec;
#endif
}