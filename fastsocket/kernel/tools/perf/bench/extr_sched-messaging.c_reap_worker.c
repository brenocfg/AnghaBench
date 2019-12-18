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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  thread_mode ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void reap_worker(pthread_t id)
{
	int proc_status;
	void *thread_status;

	if (!thread_mode) {
		/* process mode */
		wait(&proc_status);
		if (!WIFEXITED(proc_status))
			exit(1);
	} else {
		pthread_join(id, &thread_status);
	}
}