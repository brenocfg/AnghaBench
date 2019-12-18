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
struct timeval {long tv_usec; int tv_sec; } ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 struct timeval tutil_tvnow () ; 

__attribute__((used)) static int curlTimerCallback(CURLM *multi, long timeout_ms, void *userp)
{
  struct timeval* timeout = userp;

  (void)multi; /* unused */
  if(timeout_ms != -1) {
    *timeout = tutil_tvnow();
    timeout->tv_usec += timeout_ms * 1000;
  }
  else {
    timeout->tv_sec = -1;
  }
  return 0;
}