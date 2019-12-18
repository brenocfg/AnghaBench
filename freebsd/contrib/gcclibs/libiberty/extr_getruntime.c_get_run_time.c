#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tms {int tms_utime; int tms_stime; } ;
struct TYPE_4__ {int tv_sec; long tv_usec; } ;
struct TYPE_3__ {int tv_sec; long tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;

/* Variables and functions */
 long CLOCKS_PER_SEC ; 
 int GNU_HZ ; 
 long const clock () ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  times (struct tms*) ; 

long
get_run_time (void)
{
#if defined (HAVE_GETRUSAGE) && defined (HAVE_SYS_RESOURCE_H)
  struct rusage rusage;

  getrusage (0, &rusage);
  return (rusage.ru_utime.tv_sec * 1000000 + rusage.ru_utime.tv_usec
	  + rusage.ru_stime.tv_sec * 1000000 + rusage.ru_stime.tv_usec);
#else /* ! HAVE_GETRUSAGE */
#ifdef HAVE_TIMES
  struct tms tms;

  times (&tms);
  return (tms.tms_utime + tms.tms_stime) * (1000000 / GNU_HZ);
#else /* ! HAVE_TIMES */
  /* Fall back on clock and hope it's correctly implemented. */
  const long clocks_per_sec = CLOCKS_PER_SEC;
  if (clocks_per_sec <= 1000000)
    return clock () * (1000000 / clocks_per_sec);
  else
    return clock () / clocks_per_sec;
#endif  /* HAVE_TIMES */
#endif  /* HAVE_GETRUSAGE */
}