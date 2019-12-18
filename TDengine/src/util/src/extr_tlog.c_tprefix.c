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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 struct tm* localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosGetPthreadId () ; 

char *tprefix(char *prefix) {
  struct tm      Tm, *ptm;
  struct timeval timeSecs;
  time_t         curTime;

  gettimeofday(&timeSecs, NULL);
  curTime = timeSecs.tv_sec;
  ptm = localtime_r(&curTime, &Tm);

#ifndef LINUX
  sprintf(prefix, "%02d/%02d %02d:%02d:%02d.%06d 0x%lld ", ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min,
          ptm->tm_sec, (int)timeSecs.tv_usec, taosGetPthreadId());
#else
  sprintf(prefix, "%02d/%02d %02d:%02d:%02d.%06d 0x%lx ", ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min,
          ptm->tm_sec, (int)timeSecs.tv_usec, pthread_self());
#endif
  return prefix;
}