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
struct tms {void* tms_utime; void* tms_stime; } ;
struct timevar_time_def {int user; void* sys; void* wall; int /*<<< orphan*/  ggc_mem; } ;
struct TYPE_4__ {int tv_usec; void* tv_sec; } ;
struct TYPE_3__ {int tv_sec; int tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int clock () ; 
 int clocks_to_msec ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 void* ticks_to_msec ; 
 void* times (struct tms*) ; 
 int /*<<< orphan*/  timevar_enable ; 
 int /*<<< orphan*/  timevar_ggc_mem_total ; 

__attribute__((used)) static void
get_time (struct timevar_time_def *now)
{
  now->user = 0;
  now->sys  = 0;
  now->wall = 0;
  now->ggc_mem = timevar_ggc_mem_total;

  if (!timevar_enable)
    return;

  {
#ifdef USE_TIMES
    struct tms tms;
    now->wall = times (&tms)  * ticks_to_msec;
    now->user = tms.tms_utime * ticks_to_msec;
    now->sys  = tms.tms_stime * ticks_to_msec;
#endif
#ifdef USE_GETRUSAGE
    struct rusage rusage;
    getrusage (RUSAGE_SELF, &rusage);
    now->user = rusage.ru_utime.tv_sec + rusage.ru_utime.tv_usec * 1e-6;
    now->sys  = rusage.ru_stime.tv_sec + rusage.ru_stime.tv_usec * 1e-6;
#endif
#ifdef USE_CLOCK
    now->user = clock () * clocks_to_msec;
#endif
  }
}