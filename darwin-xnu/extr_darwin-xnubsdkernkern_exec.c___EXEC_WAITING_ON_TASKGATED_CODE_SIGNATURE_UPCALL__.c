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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int find_code_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((noinline)) int 
__EXEC_WAITING_ON_TASKGATED_CODE_SIGNATURE_UPCALL__(mach_port_t task_access_port, int32_t new_pid)
{
	return find_code_signature(task_access_port, new_pid);
}