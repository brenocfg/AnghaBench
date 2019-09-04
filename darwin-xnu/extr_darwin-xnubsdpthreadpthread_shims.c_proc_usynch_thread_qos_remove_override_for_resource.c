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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct uthread {int /*<<< orphan*/  uu_thread; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NULL ; 
 scalar_t__ proc_thread_qos_remove_override (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static boolean_t
proc_usynch_thread_qos_remove_override_for_resource(task_t task,
		struct uthread *uth, uint64_t tid, user_addr_t resource, int resource_type)
{
	thread_t thread = uth ? uth->uu_thread : THREAD_NULL;

	return proc_thread_qos_remove_override(task, thread, tid, resource,
			resource_type) == 0;
}