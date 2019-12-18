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
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  barf (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 void* stub1 (void*) ; 
 int /*<<< orphan*/  thread_mode ; 

__attribute__((used)) static pthread_t create_worker(void *ctx, void *(*func)(void *))
{
	pthread_attr_t attr;
	pthread_t childid;
	int err;

	if (!thread_mode) {
		/* process mode */
		/* Fork the receiver. */
		switch (fork()) {
		case -1:
			barf("fork()");
			break;
		case 0:
			(*func) (ctx);
			exit(0);
			break;
		default:
			break;
		}

		return (pthread_t)0;
	}

	if (pthread_attr_init(&attr) != 0)
		barf("pthread_attr_init:");

#ifndef __ia64__
	if (pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN) != 0)
		barf("pthread_attr_setstacksize");
#endif

	err = pthread_create(&childid, &attr, func, ctx);
	if (err != 0) {
		fprintf(stderr, "pthread_create failed: %s (%d)\n",
			strerror(err), err);
		exit(-1);
	}
	return childid;
}