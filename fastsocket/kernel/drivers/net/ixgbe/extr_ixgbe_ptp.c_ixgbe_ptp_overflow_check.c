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
struct ixgbe_adapter {scalar_t__ last_overflow_check; int /*<<< orphan*/  ptp_caps; } ;

/* Variables and functions */
 scalar_t__ IXGBE_OVERFLOW_PERIOD ; 
 int /*<<< orphan*/  ixgbe_ptp_gettime (int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ jiffies ; 
 int time_is_before_jiffies (scalar_t__) ; 

void ixgbe_ptp_overflow_check(struct ixgbe_adapter *adapter)
{
	bool timeout = time_is_before_jiffies(adapter->last_overflow_check +
					     IXGBE_OVERFLOW_PERIOD);
	struct timespec ts;

	if (timeout) {
		ixgbe_ptp_gettime(&adapter->ptp_caps, &ts);
		adapter->last_overflow_check = jiffies;
	}
}