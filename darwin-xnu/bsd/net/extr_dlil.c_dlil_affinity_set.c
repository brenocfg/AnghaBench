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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
struct TYPE_3__ {int /*<<< orphan*/  affinity_tag; } ;
typedef  TYPE_1__ thread_affinity_policy_data_t ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  policy ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY ; 
 int /*<<< orphan*/  THREAD_AFFINITY_POLICY_COUNT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  thread_policy_set (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
dlil_affinity_set(struct thread *tp, u_int32_t tag)
{
	thread_affinity_policy_data_t policy;

	bzero(&policy, sizeof (policy));
	policy.affinity_tag = tag;
	return (thread_policy_set(tp, THREAD_AFFINITY_POLICY,
	    (thread_policy_t)&policy, THREAD_AFFINITY_POLICY_COUNT));
}