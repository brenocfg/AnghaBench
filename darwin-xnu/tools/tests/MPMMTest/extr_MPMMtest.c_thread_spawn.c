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
struct TYPE_3__ {scalar_t__ tid; scalar_t__ pid; } ;
typedef  TYPE_1__ thread_id_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 
 scalar_t__ pthread_create (scalar_t__*,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 scalar_t__ threaded ; 
 int verbose ; 

__attribute__((used)) static void
thread_spawn(thread_id_t *thread, void *(fn)(void *), void *arg) {
	if (threaded) {
		kern_return_t	ret;
		ret = pthread_create(
				&thread->tid,
				NULL,
				fn,
				arg);
		if (ret != 0)
			err(1, "pthread_create()");
		if (verbose > 1)
			printf("created pthread %p\n", thread->tid);
	} else {
		thread->pid = fork();
		if (thread->pid == 0) {
			if (verbose > 1)
				printf("calling %p(%p)\n", fn, arg);
			fn(arg);
			exit(0);
		}
		if (verbose > 1)
			printf("forked pid %d\n", thread->pid);
	}
}