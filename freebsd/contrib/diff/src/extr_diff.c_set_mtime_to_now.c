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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int ST_MTIM_NSEC; } ;
struct stat {int /*<<< orphan*/  st_mtime; TYPE_1__ st_mtim; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_mtime_to_now (struct stat *st)
{
#ifdef ST_MTIM_NSEC

# if HAVE_CLOCK_GETTIME && defined CLOCK_REALTIME
  if (clock_gettime (CLOCK_REALTIME, &st->st_mtim) == 0)
    return;
# endif

# if HAVE_GETTIMEOFDAY
  {
    struct timeval timeval;
    if (gettimeofday (&timeval, 0) == 0)
      {
	st->st_mtime = timeval.tv_sec;
	st->st_mtim.ST_MTIM_NSEC = timeval.tv_usec * 1000;
	return;
      }
  }
# endif

#endif /* ST_MTIM_NSEC */

  time (&st->st_mtime);
}