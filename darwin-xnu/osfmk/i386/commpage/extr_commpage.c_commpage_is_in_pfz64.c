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
typedef  int uint32_t ;
typedef  scalar_t__ addr64_t ;

/* Variables and functions */
 scalar_t__ _COMM_TEXT_PFZ_END_OFFSET ; 
 scalar_t__ _COMM_TEXT_PFZ_START_OFFSET ; 
 scalar_t__ commpage_text64_location ; 

uint32_t
commpage_is_in_pfz64(addr64_t addr64)
{
	if ( (addr64 >= (commpage_text64_location + _COMM_TEXT_PFZ_START_OFFSET))
	     && (addr64 <  (commpage_text64_location + _COMM_TEXT_PFZ_END_OFFSET))) {
		return 1;
	}
	else
		return 0;
}