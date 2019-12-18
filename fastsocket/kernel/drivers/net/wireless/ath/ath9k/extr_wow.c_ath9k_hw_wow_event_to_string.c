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
typedef  int u32 ;

/* Variables and functions */
 int AH_WOW_BEACON_MISS ; 
 int AH_WOW_LINK_CHANGE ; 
 int AH_WOW_MAGIC_PATTERN_EN ; 
 int AH_WOW_USER_PATTERN_EN ; 

const char *ath9k_hw_wow_event_to_string(u32 wow_event)
{
	if (wow_event & AH_WOW_MAGIC_PATTERN_EN)
		return "Magic pattern";
	if (wow_event & AH_WOW_USER_PATTERN_EN)
		return "User pattern";
	if (wow_event & AH_WOW_LINK_CHANGE)
		return "Link change";
	if (wow_event & AH_WOW_BEACON_MISS)
		return "Beacon miss";

	return  "unknown reason";
}