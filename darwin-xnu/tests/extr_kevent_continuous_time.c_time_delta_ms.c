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
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ mach_continuous_time () ; 
 scalar_t__ tick_to_ms (scalar_t__) ; 

__attribute__((used)) static uint64_t time_delta_ms(void){
	uint64_t abs_now = mach_absolute_time();
	uint64_t cnt_now = mach_continuous_time();;
	return tick_to_ms(cnt_now) - tick_to_ms(abs_now);
}