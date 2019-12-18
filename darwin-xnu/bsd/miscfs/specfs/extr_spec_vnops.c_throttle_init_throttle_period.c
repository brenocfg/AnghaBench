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
typedef  int /*<<< orphan*/  throttle_period_size ;
struct _throttle_io_info_t {scalar_t__ throttle_is_fusion_with_priority; int* throttle_io_periods; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ PE_get_default (char*,int*,int) ; 
 scalar_t__ PE_parse_boot_argn (char*,int*,int) ; 
 size_t THROTTLE_LEVEL_TIER1 ; 
 size_t THROTTLE_LEVEL_TIER2 ; 
 size_t THROTTLE_LEVEL_TIER3 ; 
 scalar_t__ TRUE ; 
 int* throttle_io_period_msecs ; 
 int* throttle_io_period_ssd_msecs ; 

__attribute__((used)) static void
throttle_init_throttle_period(struct _throttle_io_info_t *info, boolean_t isssd)
{
	int throttle_period_size;

	/*
	 * The hierarchy of throttle period values is as follows:
	 * - Global defaults
	 * - Device tree properties
	 * - Boot-args
	 * All values are specified in msecs.
	 */

	/* Assign global defaults */
	if ((isssd == TRUE) && (info->throttle_is_fusion_with_priority == 0))
		info->throttle_io_periods = &throttle_io_period_ssd_msecs[0];
	else
		info->throttle_io_periods = &throttle_io_period_msecs[0];

	/* Override global values with device-tree properties */
	if (PE_get_default("kern.io_throttle_period_tier1", &throttle_period_size, sizeof(throttle_period_size)))
		info->throttle_io_periods[THROTTLE_LEVEL_TIER1] = throttle_period_size;
	
	if (PE_get_default("kern.io_throttle_period_tier2", &throttle_period_size, sizeof(throttle_period_size)))
		info->throttle_io_periods[THROTTLE_LEVEL_TIER2] = throttle_period_size;

	if (PE_get_default("kern.io_throttle_period_tier3", &throttle_period_size, sizeof(throttle_period_size)))
		info->throttle_io_periods[THROTTLE_LEVEL_TIER3] = throttle_period_size;
	
	/* Override with boot-args */
	if (PE_parse_boot_argn("io_throttle_period_tier1", &throttle_period_size, sizeof(throttle_period_size)))
		info->throttle_io_periods[THROTTLE_LEVEL_TIER1] = throttle_period_size;
	
	if (PE_parse_boot_argn("io_throttle_period_tier2", &throttle_period_size, sizeof(throttle_period_size)))
		info->throttle_io_periods[THROTTLE_LEVEL_TIER2] = throttle_period_size;

	if (PE_parse_boot_argn("io_throttle_period_tier3", &throttle_period_size, sizeof(throttle_period_size)))
		info->throttle_io_periods[THROTTLE_LEVEL_TIER3] = throttle_period_size;

}