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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

void taosMsleep(int mseconds) {
  struct timeval timeout;
  int            seconds, useconds;

  seconds = mseconds / 1000;
  useconds = (mseconds % 1000) * 1000;
  timeout.tv_sec = seconds;
  timeout.tv_usec = useconds;

  /* sigset_t set; */
  /* sigemptyset(&set); */
  /* sigaddset(&set, SIGALRM); */
  /* pthread_sigmask(SIG_BLOCK, &set, NULL); */

  select(0, NULL, NULL, NULL, &timeout);

  /* pthread_sigmask(SIG_UNBLOCK, &set, NULL); */
}