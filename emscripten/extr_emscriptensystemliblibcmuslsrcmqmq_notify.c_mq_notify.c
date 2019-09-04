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
struct TYPE_2__ {void* sival_ptr; } ;
typedef  struct sigevent {scalar_t__ sigev_notify; int sigev_signo; TYPE_1__ sigev_value; int /*<<< orphan*/ * sigev_notify_attributes; } const sigevent ;
struct args {int sock; int /*<<< orphan*/  barrier; struct sigevent const* sev; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  mqd_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 scalar_t__ SIGEV_THREAD ; 
 int SOCK_CLOEXEC ; 
 int SOCK_RAW ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  SYS_mq_notify ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct args*) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sigevent const*) ; 

int mq_notify(mqd_t mqd, const struct sigevent *sev)
{
	struct args args = { .sev = sev };
	pthread_attr_t attr;
	pthread_t td;
	int s;
	struct sigevent sev2;
	static const char zeros[32];

	if (!sev || sev->sigev_notify != SIGEV_THREAD)
		return syscall(SYS_mq_notify, mqd, sev);

	s = socket(AF_NETLINK, SOCK_RAW|SOCK_CLOEXEC, 0);
	if (s < 0) return -1;
	args.sock = s;

	if (sev->sigev_notify_attributes) attr = *sev->sigev_notify_attributes;
	else pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_barrier_init(&args.barrier, 0, 2);

	if (pthread_create(&td, &attr, start, &args)) {
		__syscall(SYS_close, s);
		errno = EAGAIN;
		return -1;
	}

	pthread_barrier_wait(&args.barrier);
	pthread_barrier_destroy(&args.barrier);

	sev2.sigev_notify = SIGEV_THREAD;
	sev2.sigev_signo = s;
	sev2.sigev_value.sival_ptr = (void *)&zeros;

	if (syscall(SYS_mq_notify, mqd, &sev2) < 0) {
		pthread_cancel(td);
		__syscall(SYS_close, s);
		return -1;
	}

	return 0;
}