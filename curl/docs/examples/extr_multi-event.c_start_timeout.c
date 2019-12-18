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
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int start_timeout(CURLM *multi, long timeout_ms, void *userp)
{
  if(timeout_ms < 0) {
    evtimer_del(timeout);
  }
  else {
    if(timeout_ms == 0)
      timeout_ms = 1; /* 0 means directly call socket_action, but we'll do it
                         in a bit */
    struct timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    evtimer_del(timeout);
    evtimer_add(timeout, &tv);
  }
  return 0;
}