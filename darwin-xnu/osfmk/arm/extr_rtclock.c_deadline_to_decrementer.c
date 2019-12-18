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

/* Variables and functions */
 scalar_t__ DECREMENTER_MAX ; 
 int DECREMENTER_MIN ; 

__attribute__((used)) static int
deadline_to_decrementer(uint64_t deadline,
                        uint64_t now)
{
	uint64_t delt;

	if (deadline <= now)
		return DECREMENTER_MIN;
	else {
		delt = deadline - now;

		return (delt >= (DECREMENTER_MAX + 1)) ? DECREMENTER_MAX : ((delt >= (DECREMENTER_MIN + 1)) ? (int)delt : DECREMENTER_MIN);
	}
}