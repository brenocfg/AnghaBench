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
struct timespec {int dummy; } ;
struct smi_info {size_t intf_num; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;

/* Variables and functions */
 unsigned int NSEC_PER_USEC ; 
 int SI_SM_CALL_WITH_DELAY ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 int /*<<< orphan*/  ipmi_si_is_busy (struct timespec*) ; 
 int /*<<< orphan*/  ipmi_si_set_not_busy (struct timespec*) ; 
 unsigned int* kipmid_max_busy_us ; 
 size_t num_max_busy_us ; 
 int /*<<< orphan*/  timespec_add_ns (struct timespec*,unsigned int) ; 
 scalar_t__ timespec_compare (struct timespec*,struct timespec*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipmi_thread_busy_wait(enum si_sm_result smi_result,
				const struct smi_info *smi_info,
				struct timespec *busy_until)
{
	unsigned int max_busy_us = 0;

	if (smi_info->intf_num < num_max_busy_us)
		max_busy_us = kipmid_max_busy_us[smi_info->intf_num];
	if (max_busy_us == 0 || smi_result != SI_SM_CALL_WITH_DELAY)
		ipmi_si_set_not_busy(busy_until);
	else if (!ipmi_si_is_busy(busy_until)) {
		getnstimeofday(busy_until);
		timespec_add_ns(busy_until, max_busy_us*NSEC_PER_USEC);
	} else {
		struct timespec now;
		getnstimeofday(&now);
		if (unlikely(timespec_compare(&now, busy_until) > 0)) {
			ipmi_si_set_not_busy(busy_until);
			return 0;
		}
	}
	return 1;
}