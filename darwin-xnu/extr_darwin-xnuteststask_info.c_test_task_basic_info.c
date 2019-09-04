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
typedef  int uint64_t ;
struct TYPE_2__ {int seconds; int microseconds; } ;
typedef  TYPE_1__ time_value_t ;
typedef  int /*<<< orphan*/  task_info_t ;
typedef  int /*<<< orphan*/  task_flavor_t ;
typedef  int /*<<< orphan*/  task_basic_info_64_data_t ;
typedef  int /*<<< orphan*/  task_basic_info_32_data_t ;
typedef  int policy_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  mach_task_basic_info_data_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int kern_return_t ;
typedef  scalar_t__ integer_t ;
typedef  enum info_kind { ____Placeholder_info_kind } info_kind ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MAX_RES ; 
 int /*<<< orphan*/  GET_POLICY ; 
 int /*<<< orphan*/  GET_RESIDENT_SIZE ; 
 int /*<<< orphan*/  GET_SUSPEND_COUNT ; 
 int /*<<< orphan*/  GET_SYS_TIME ; 
 int /*<<< orphan*/  GET_USER_TIME ; 
 int /*<<< orphan*/  GET_VIRTUAL_SIZE ; 
#define  INFO_32 133 
#define  INFO_32_2 132 
#define  INFO_64 131 
#define  INFO_64_2 130 
#define  INFO_MACH 129 
#define  INFO_MAX 128 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  MACH_TASK_BASIC_INFO ; 
 int /*<<< orphan*/  MACH_TASK_BASIC_INFO_COUNT ; 
 int MAP_ANON ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int MAP_PRIVATE ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long long POLICY_TIMESHARE ; 
 int /*<<< orphan*/  PROT_WRITE ; 
 int /*<<< orphan*/  TASK_BASIC2_INFO_32 ; 
 int /*<<< orphan*/  TASK_BASIC_INFO_32 ; 
 int /*<<< orphan*/  TASK_BASIC_INFO_32_COUNT ; 
 int /*<<< orphan*/  TASK_BASIC_INFO_64 ; 
 int /*<<< orphan*/  TASK_BASIC_INFO_64_COUNT ; 
 int /*<<< orphan*/  T_ASSERT_EQ (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*) ; 
 int /*<<< orphan*/  T_ASSERT_MACH_ERROR (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (scalar_t__,char*) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int,char*) ; 
 int /*<<< orphan*/  T_EXPECT_EQ (int,unsigned long long,char*) ; 
 int /*<<< orphan*/  T_EXPECT_GE (int,int,char*) ; 
 int /*<<< orphan*/  T_EXPECT_NE (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_FAIL (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 int /*<<< orphan*/  T_WITH_ERRNO ; 
 int /*<<< orphan*/  do_factorial_task () ; 
 scalar_t__ dt_waitpid (scalar_t__,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int info_get (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_development_kernel () ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  memset (void*,char,scalar_t__) ; 
 void* mmap (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,scalar_t__) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int task_for_pid (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int task_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int task_resume (int /*<<< orphan*/ ) ; 
 int task_suspend (int /*<<< orphan*/ ) ; 

void
test_task_basic_info(enum info_kind kind)
{
#define BEFORE 0
#define AFTER 1

	T_SETUPBEGIN;
	int is_dev = is_development_kernel();
	T_QUIET;
	T_ASSERT_TRUE(is_dev, "verify development kernel is running");
	T_SETUPEND;

	task_info_t info_data[2];
	task_basic_info_32_data_t basic_info_32_data[2];
#if defined(__arm__) || defined(__arm64__)
	task_basic_info_64_2_data_t basic_info_64_2_data[2];
#else
	task_basic_info_64_data_t basic_info_64_data[2];
#endif /* defined(__arm__) || defined(__arm64__) */
	mach_task_basic_info_data_t mach_basic_info_data[2];

	kern_return_t kr;
	mach_msg_type_number_t count;
	task_flavor_t flavor = 0;
	integer_t suspend_count;
	uint64_t resident_size_diff;
	uint64_t virtual_size_diff;

	void * tmp_map = NULL;
	pid_t child_pid;
	mach_port_name_t child_task;
	/*for dt_waitpid*/
	int timeout     = 10; // change to max timeout
	int exit_status = 0;

	switch (kind) {
	case INFO_32:
	case INFO_32_2:
		info_data[BEFORE] = (task_info_t)&basic_info_32_data[BEFORE];
		info_data[AFTER]  = (task_info_t)&basic_info_32_data[AFTER];
		count             = TASK_BASIC_INFO_32_COUNT;
		flavor            = TASK_BASIC_INFO_32;

		if (kind == INFO_32_2) {
			flavor = TASK_BASIC2_INFO_32;
		}

		break;
#if defined(__arm__) || defined(__arm64__)
	case INFO_64:
		T_ASSERT_FAIL("invalid basic info kind");
		break;

	case INFO_64_2:
		info_data[BEFORE] = (task_info_t)&basic_info_64_2_data[BEFORE];
		info_data[AFTER]  = (task_info_t)&basic_info_64_2_data[AFTER];
		count             = TASK_BASIC_INFO_64_2_COUNT;
		flavor            = TASK_BASIC_INFO_64_2;
		break;

#else
	case INFO_64:
		info_data[BEFORE] = (task_info_t)&basic_info_64_data[BEFORE];
		info_data[AFTER]  = (task_info_t)&basic_info_64_data[AFTER];
		count             = TASK_BASIC_INFO_64_COUNT;
		flavor            = TASK_BASIC_INFO_64;
		break;

	case INFO_64_2:
		T_ASSERT_FAIL("invalid basic info kind");
		break;
#endif /* defined(__arm__) || defined(__arm64__) */
	case INFO_MACH:
		info_data[BEFORE] = (task_info_t)&mach_basic_info_data[BEFORE];
		info_data[AFTER]  = (task_info_t)&mach_basic_info_data[AFTER];
		count             = MACH_TASK_BASIC_INFO_COUNT;
		flavor            = MACH_TASK_BASIC_INFO;
		break;
	case INFO_MAX:
	default:
		T_ASSERT_FAIL("invalid basic info kind");
		break;
	}

	kr = task_info(mach_task_self(), flavor, info_data[BEFORE], &count);

	T_ASSERT_MACH_SUCCESS(kr, "verify task_info succeeded");

	do_factorial_task();

	/*
	 * Allocate virtual and resident memory.
	 */
	tmp_map = mmap(0, PAGE_SIZE, PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

	T_WITH_ERRNO;
	T_EXPECT_NE(tmp_map, MAP_FAILED, "verify mmap call is successful");

	memset(tmp_map, 'm', PAGE_SIZE);

	child_pid = fork();

	T_ASSERT_POSIX_SUCCESS(child_pid, "verify process can be forked");

	if (child_pid == 0) {
		/*
		 * This will suspend the child process.
		 */
		kr = task_suspend(mach_task_self());
		exit(kr);
	}

	/*
	 * Wait for the child process to suspend itself.
	 */
	sleep(1);

	kr = task_for_pid(mach_task_self(), child_pid, &child_task);
	T_ASSERT_MACH_SUCCESS(kr, "verify task_for_pid succeeded.  check sudo if failed");

	/*
	 * Verify the suspend_count for child and resume it.
	 */

	kr = task_info(child_task, flavor, info_data[AFTER], &count);
	T_ASSERT_MACH_SUCCESS(kr, "verify task_info call succeeded");

	suspend_count = (integer_t)(info_get(kind, GET_SUSPEND_COUNT, info_data[AFTER]));
	T_ASSERT_EQ(suspend_count, 1, "verify task_info shows correct suspend_count");

	kr = task_resume(child_task);
	T_ASSERT_MACH_SUCCESS(kr, "verify task_resume succeeded");

	/*
	 * reap kr from task_suspend call in child
	 */
	if (dt_waitpid(child_pid, &exit_status, NULL, timeout)) {
		T_ASSERT_MACH_SUCCESS(exit_status, "verify child task_suspend is successful");
	} else {
		T_FAIL("dt_waitpid failed");
	}

	kr = task_info(mach_task_self(), flavor, info_data[AFTER], &count);
	T_ASSERT_MACH_SUCCESS(kr, "verify task_info call succeeded");

	resident_size_diff = info_get(kind, GET_RESIDENT_SIZE, info_data[AFTER]) - info_get(kind, GET_RESIDENT_SIZE, info_data[BEFORE]);
	virtual_size_diff  = info_get(kind, GET_VIRTUAL_SIZE, info_data[AFTER]) - info_get(kind, GET_VIRTUAL_SIZE, info_data[BEFORE]);

	/*
	 * INFO_32_2 gets the max resident size instead of the current resident size
	 * 32 KB tolerance built into test.  The returned value is generally between 0 and 16384
	 *
	 * max resident size is a discrete field in INFO_MACH, so it's handled differently
	 */
	if (kind == INFO_32_2) {
		T_EXPECT_EQ(resident_size_diff % 4096, 0ULL, "verify task_info returns valid max resident_size");
		T_EXPECT_GE(resident_size_diff, 0ULL, "verify task_info returns non-negative max resident_size");
		T_EXPECT_GE(virtual_size_diff, (unsigned long long)PAGE_SIZE, "verify task_info returns valid virtual_size");
	} else {
		T_EXPECT_GE(resident_size_diff, (unsigned long long)PAGE_SIZE, "task_info returns valid resident_size");
		T_EXPECT_GE(virtual_size_diff, (unsigned long long)PAGE_SIZE, "task_info returns valid virtual_size");
	}

	if (kind == INFO_MACH) {
		resident_size_diff = info_get(kind, GET_MAX_RES, info_data[AFTER]) - info_get(kind, GET_MAX_RES, info_data[BEFORE]);
		T_EXPECT_EQ(resident_size_diff % 4096, 0ULL, "verify task_info returns valid max resident_size");
		T_EXPECT_GE(resident_size_diff, 0ULL, "verify task_info returns non-negative max resident_size");
		T_EXPECT_GE(info_get(kind, GET_MAX_RES, info_data[AFTER]), info_get(kind, GET_RESIDENT_SIZE, info_data[AFTER]),
		            "verify max resident size is greater than or equal to curr resident size");
	}

	do_factorial_task();

	/*
	 * These counters give time for threads that have terminated. We dont have any, so checking for zero.
	 */

	time_value_t * user_tv = (time_value_t *)(info_get(kind, GET_USER_TIME, info_data[BEFORE]));
	T_EXPECT_EQ((user_tv->seconds + user_tv->microseconds / 1000000), 0, "verify task_info shows valid user time");

	time_value_t * sys_tv = (time_value_t *)(info_get(kind, GET_SYS_TIME, info_data[BEFORE]));
	T_EXPECT_EQ(sys_tv->seconds + (sys_tv->microseconds / 1000000), 0, "verify task_info shows valid system time");

	/*
	 * The default value for non-kernel tasks is TIMESHARE.
	 */

	policy_t pt = (policy_t)info_get(kind, GET_POLICY, info_data[BEFORE]);

	T_EXPECT_EQ(pt, POLICY_TIMESHARE, "verify task_info shows valid policy");

	/*
	 * This is a negative case.
	 */

	count--;
	kr = task_info(mach_task_self(), flavor, info_data[AFTER], &count);

	T_ASSERT_MACH_ERROR(kr, KERN_INVALID_ARGUMENT,
	                    "Negative test case: task_info should verify that count is at least equal to what is defined in API");

	/*
	 * deallocate memory
	 */
	munmap(tmp_map, PAGE_SIZE);

	return;

#undef BEFORE
#undef AFTER
}