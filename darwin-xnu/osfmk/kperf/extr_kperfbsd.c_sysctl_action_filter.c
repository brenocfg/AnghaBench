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
typedef  int uint64_t ;
struct sysctl_req {scalar_t__ newptr; scalar_t__ oldptr; } ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  inputs ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int copyin (scalar_t__,int*,int) ; 
 int copyout (int*,scalar_t__,int) ; 
 int kperf_action_get_filter (unsigned int,int*) ; 
 int kperf_action_set_filter (unsigned int,int) ; 
 int kperf_port_to_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sysctl_action_filter(struct sysctl_req *req, bool is_task_t)
{
	int error = 0;
	uint64_t inputs[2] = {};

	assert(req != NULL);

	if (req->newptr == USER_ADDR_NULL) {
		return EFAULT;
	}

	if ((error = copyin(req->newptr, inputs, sizeof(inputs)))) {
		return error;
	}

	unsigned int actionid = (unsigned int)inputs[0];
	int new_filter = (int)inputs[1];

	if (req->oldptr != USER_ADDR_NULL) {
		int filter_out;
		if ((error = kperf_action_get_filter(actionid, &filter_out))) {
			return error;
		}

		inputs[1] = filter_out;
		return copyout(inputs, req->oldptr, sizeof(inputs));
	} else {
		int pid = is_task_t ? kperf_port_to_pid((mach_port_name_t)new_filter)
				: new_filter;

		return kperf_action_set_filter(actionid, pid);
	}
}