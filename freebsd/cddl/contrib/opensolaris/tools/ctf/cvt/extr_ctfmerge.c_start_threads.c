#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wq_nthreads; int /*<<< orphan*/ * wq_thread; } ;
typedef  TYPE_1__ workqueue_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  handle_sig ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ worker_thread ; 

__attribute__((used)) static void
start_threads(workqueue_t *wq)
{
	sigset_t sets;
	int i;

	sigemptyset(&sets);
	sigaddset(&sets, SIGINT);
	sigaddset(&sets, SIGQUIT);
	sigaddset(&sets, SIGTERM);
	pthread_sigmask(SIG_BLOCK, &sets, NULL);

	for (i = 0; i < wq->wq_nthreads; i++) {
		pthread_create(&wq->wq_thread[i], NULL,
		    (void *(*)(void *))worker_thread, wq);
	}

#ifdef illumos
	sigset(SIGINT, handle_sig);
	sigset(SIGQUIT, handle_sig);
	sigset(SIGTERM, handle_sig);
#else
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	signal(SIGTERM, handle_sig);
#endif
	pthread_sigmask(SIG_UNBLOCK, &sets, NULL);
}