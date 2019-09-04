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
struct TYPE_3__ {int tid; int pid; } ;
typedef  TYPE_1__ thread_id_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ pthread_join (int,int /*<<< orphan*/ *) ; 
 scalar_t__ threaded ; 
 int verbose ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thread_join(thread_id_t *thread) {
	if (threaded) {
		kern_return_t	ret;
		if (verbose > 1)
			printf("joining thread %p\n", thread->tid);
		ret = pthread_join(thread->tid, NULL);
		if (ret != KERN_SUCCESS)
			err(1, "pthread_join(%p)", thread->tid);
	} else {
		int	stat;
		if (verbose > 1)
			printf("waiting for pid %d\n", thread->pid);
		waitpid(thread->pid, &stat, 0);
	}
}