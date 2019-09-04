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
typedef  scalar_t__ uint64_t ;
struct sysctl_req {scalar_t__ newptr; scalar_t__ oldptr; } ;
typedef  int /*<<< orphan*/  inputs ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int copyin (scalar_t__,scalar_t__*,int) ; 
 int copyout (scalar_t__*,scalar_t__,int) ; 
 int kperf_timer_get_period (unsigned int,scalar_t__*) ; 
 int kperf_timer_set_period (unsigned int,scalar_t__) ; 

__attribute__((used)) static int
sysctl_timer_period(struct sysctl_req *req)
{
	int error;
	uint64_t inputs[2] = {};

	assert(req != NULL);

	if (req->newptr == USER_ADDR_NULL) {
		return EFAULT;
	}

	if ((error = copyin(req->newptr, inputs, sizeof(inputs)))) {
		return error;
	}

	unsigned int timer = (unsigned int)inputs[0];
	uint64_t new_period = inputs[1];

	if (req->oldptr != USER_ADDR_NULL) {
		uint64_t period_out = 0;
		if ((error = kperf_timer_get_period(timer, &period_out))) {
			return error;
		}

		inputs[1] = period_out;

		return copyout(inputs, req->oldptr, sizeof(inputs));
	} else {
		return kperf_timer_set_period(timer, new_period);
	}
}