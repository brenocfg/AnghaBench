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
 int /*<<< orphan*/  MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_decrementer_max ; 
 scalar_t__ rtc_decrementer_min ; 

__attribute__((used)) static uint64_t
deadline_to_decrementer(
	uint64_t	deadline,
	uint64_t	now)
{
	uint64_t	delta;

	if (deadline <= now)
		return rtc_decrementer_min;
	else {
		delta = deadline - now;
		return MIN(MAX(rtc_decrementer_min,delta),rtc_decrementer_max); 
	}
}