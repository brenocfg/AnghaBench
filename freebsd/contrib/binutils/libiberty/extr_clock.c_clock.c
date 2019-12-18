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
struct tms {int proc_user_time; int proc_system_time; int child_user_time; int child_system_time; } ;
struct TYPE_4__ {int tv_sec; long tv_usec; } ;
struct TYPE_3__ {int tv_sec; long tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;

/* Variables and functions */
 int GNU_HZ ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  times (struct tms*) ; 

long
clock (void)
{
#ifdef HAVE_GETRUSAGE
  struct rusage rusage;

  getrusage (0, &rusage);
  return (rusage.ru_utime.tv_sec * 1000000 + rusage.ru_utime.tv_usec
	  + rusage.ru_stime.tv_sec * 1000000 + rusage.ru_stime.tv_usec);
#else
#ifdef HAVE_TIMES
  struct tms tms;

  times (&tms);
  return (tms.tms_utime + tms.tms_stime) * (1000000 / GNU_HZ);
#else
#ifdef VMS
  struct
    {
      int proc_user_time;
      int proc_system_time;
      int child_user_time;
      int child_system_time;
    } vms_times;

  times (&vms_times);
  return (vms_times.proc_user_time + vms_times.proc_system_time) * 10000;
#else
  /* A fallback, if nothing else available. */
  return 0;
#endif /* VMS */
#endif /* HAVE_TIMES */
#endif /* HAVE_GETRUSAGE */
}