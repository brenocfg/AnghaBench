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
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int close (int) ; 
 int kqueue () ; 
 int /*<<< orphan*/  poll_kqueue ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int timeout_ms ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
run_test()
{
	int fd = kqueue();
	T_QUIET; T_ASSERT_POSIX_SUCCESS(fd, "kqueue");

	pthread_t thread;
	int rv = pthread_create(&thread, NULL, poll_kqueue,
	                        (void *)(uintptr_t)fd);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_create");

	usleep(timeout_ms * 1000);

	rv = close(fd);
	T_ASSERT_POSIX_SUCCESS(rv, "close");

	rv = pthread_join(thread, NULL);
	T_QUIET; T_ASSERT_POSIX_SUCCESS(rv, "pthread_join");
}