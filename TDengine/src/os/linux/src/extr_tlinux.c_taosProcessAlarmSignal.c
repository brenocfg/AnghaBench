#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_t ;
struct TYPE_4__ {int /*<<< orphan*/  _tid; } ;
struct sigevent {int /*<<< orphan*/  sigev_signo; TYPE_1__ _sigev_un; int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_6__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct itimerspec {TYPE_3__ it_interval; TYPE_2__ it_value; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int MSECONDS_PER_TICK ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  __NR_gettid ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigwait (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 
 int timer_create (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmrError (char*,...) ; 

void *taosProcessAlarmSignal(void *tharg) {
  // Block the signal
  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGALRM);
  sigprocmask(SIG_BLOCK, &sigset, NULL);
  void (*callback)(int) = tharg;

  timer_t         timerId;
  struct sigevent sevent;
  sevent.sigev_notify = SIGEV_THREAD_ID;
  sevent._sigev_un._tid = syscall(__NR_gettid);
  sevent.sigev_signo = SIGALRM;

  if (timer_create(CLOCK_REALTIME, &sevent, &timerId) == -1) {
    tmrError("Failed to create timer");
  }

  struct itimerspec ts;
  ts.it_value.tv_sec = 0;
  ts.it_value.tv_nsec = 1000000 * MSECONDS_PER_TICK;
  ts.it_interval.tv_sec = 0;
  ts.it_interval.tv_nsec = 1000000 * MSECONDS_PER_TICK;

  if (timer_settime(timerId, 0, &ts, NULL)) {
    tmrError("Failed to init timer");
    return NULL;
  }

  int signo;
  while (1) {
    if (sigwait(&sigset, &signo)) {
      tmrError("Failed to wait signal: number %d", signo);
      continue;
    }
    /* printf("Signal handling: number %d ......\n", signo); */

    callback(0);
  }

  assert(0);
  return NULL;
}