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
typedef  int uint32_t ;
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_realtime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pthread_t
create_thread(void *(*start_routine)(void *), uint32_t priority)
{
	int rv;
	pthread_t new_thread;
	pthread_attr_t attr;

	struct sched_param param = { .sched_priority = (int)priority };

	rv = pthread_attr_init(&attr);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_attr_init");

	rv = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_attr_setdetachstate");

	rv = pthread_attr_setschedparam(&attr, &param);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_attr_setschedparam");

	rv = pthread_create(&new_thread, &attr, start_routine, NULL);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_create");

	if (priority == 97)
		set_realtime(new_thread);

	rv = pthread_attr_destroy(&attr);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_attr_destroy");

	return new_thread;
}