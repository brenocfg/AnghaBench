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
typedef  void* uint32_t ;
struct TYPE_2__ {scalar_t__ preemptible; void* computation; void* constraint; void* period; } ;
typedef  TYPE_1__ thread_time_constraint_policy_data_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY ; 
 int /*<<< orphan*/  THREAD_TIME_CONSTRAINT_POLICY_COUNT ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 scalar_t__ nanos_to_abs (int) ; 
 int /*<<< orphan*/  pthread_mach_thread_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_policy_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_realtime(pthread_t thread) {
	kern_return_t kr;
	thread_time_constraint_policy_data_t pol;

	mach_port_t target_thread = pthread_mach_thread_np(thread);
	T_QUIET; T_ASSERT_NOTNULL(target_thread, "pthread_mach_thread_np");

	/* 1s 100ms 10ms */
	pol.period      = (uint32_t)nanos_to_abs(1000000000);
	pol.constraint  = (uint32_t)nanos_to_abs(100000000);
	pol.computation = (uint32_t)nanos_to_abs(10000000);

	pol.preemptible = 0; /* Ignored by OS */
	kr = thread_policy_set(target_thread, THREAD_TIME_CONSTRAINT_POLICY, (thread_policy_t) &pol,
	                       THREAD_TIME_CONSTRAINT_POLICY_COUNT);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "thread_policy_set(THREAD_TIME_CONSTRAINT_POLICY)");
}