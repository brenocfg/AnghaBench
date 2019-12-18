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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ IWLAGN_RTC_INST_LOWER_BOUND ; 
 scalar_t__ IWLAGN_RTC_INST_UPPER_BOUND ; 
 scalar_t__ iwlagn_hw_valid_rtc_data_addr (scalar_t__) ; 

__attribute__((used)) static bool iwl_testmode_valid_hw_addr(u32 addr)
{
	if (iwlagn_hw_valid_rtc_data_addr(addr))
		return true;

	if (IWLAGN_RTC_INST_LOWER_BOUND <= addr &&
	    addr < IWLAGN_RTC_INST_UPPER_BOUND)
		return true;

	return false;
}