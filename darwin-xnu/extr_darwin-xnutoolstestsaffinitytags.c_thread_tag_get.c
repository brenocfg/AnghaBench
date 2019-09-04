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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
struct TYPE_2__ {int affinity_tag; } ;
typedef  TYPE_1__ thread_affinity_policy_data_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY_COUNT ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ thread_policy_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
thread_tag_get(thread_t thread)
{
	kern_return_t			ret;
	boolean_t			get_default = FALSE;
	thread_affinity_policy_data_t	policy;
	mach_msg_type_number_t		count = THREAD_AFFINITY_POLICY_COUNT;

	ret = thread_policy_get(
			thread, THREAD_AFFINITY_POLICY,
			(thread_policy_t) &policy, &count, &get_default);
	if (ret != KERN_SUCCESS) {
		printf("thread_policy_set(1) returned %d\n", ret);
		exit(1);
	}

	return policy.affinity_tag;
}