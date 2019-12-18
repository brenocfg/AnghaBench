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
typedef  void* u_int ;
typedef  int /*<<< orphan*/  time_t ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_3__ {void* nt_useconds; void* nt_seconds; } ;
typedef  TYPE_1__ nfstime ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

time_t
clocktime(nfstime *nt)
{
  static struct timeval now;	/* keep last time, as default */

  if (gettimeofday(&now, NULL) < 0) {
    plog(XLOG_ERROR, "clocktime: gettimeofday: %m");
    /* hack: force time to have incremented by at least 1 second */
    now.tv_sec++;
  }
  /* copy seconds and microseconds. may demote a long to an int */
  if (nt) {
    nt->nt_seconds = (u_int) now.tv_sec;
    nt->nt_useconds = (u_int) now.tv_usec;
  }
  return (time_t) now.tv_sec;
}