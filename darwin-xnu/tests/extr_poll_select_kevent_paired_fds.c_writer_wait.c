#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  out_fd; int /*<<< orphan*/  in_fd; int /*<<< orphan*/  sem; } ;
struct TYPE_6__ {int wr_kind; TYPE_1__ wr_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_OPERATION_TIMED_OUT ; 
#define  PROCESS_WRITER 129 
 TYPE_3__ READ_SETUP_timeout ; 
#define  THREAD_WRITER 128 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  semaphore_timedwait (int /*<<< orphan*/ ,TYPE_3__) ; 
 TYPE_2__ shared ; 

__attribute__((used)) static void
writer_wait(void)
{
	switch (shared.wr_kind) {
	case THREAD_WRITER:
		T_LOG("wait shared.wr_wait.sem");
		kern_return_t kret = semaphore_timedwait(shared.wr_wait.sem, READ_SETUP_timeout);

		if (kret == KERN_OPERATION_TIMED_OUT) {
			T_ASSERT_FAIL("THREAD_WRITER semaphore timedout after %d seconds", READ_SETUP_timeout.tv_sec);
		}
		T_QUIET;
		T_ASSERT_MACH_SUCCESS(kret, "semaphore_timedwait shared.wr_wait.sem");
		break;

	case PROCESS_WRITER: {
		char tmp;
		close(shared.wr_wait.in_fd);
		T_QUIET; T_ASSERT_POSIX_SUCCESS(read(
				shared.wr_wait.out_fd, &tmp, 1), NULL);
		break;
	}
	}

	T_LOG("writer woken up, starting to write");
}