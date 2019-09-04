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
typedef  int /*<<< orphan*/  arm_debug_state_t ;
typedef  int /*<<< orphan*/  arm_context_t ;

/* Variables and functions */
 int CONFIG_THREAD_MAX ; 
 int THREAD_CHUNK ; 
 int USER_SS_ZONE_ALLOC_SIZE ; 
 void* ads_zone ; 
 void* user_ss_zone ; 
 void* zinit (int,int,int,char*) ; 

void
machine_thread_init(void)
{
	ads_zone = zinit(sizeof(arm_debug_state_t),
	                 THREAD_CHUNK * (sizeof(arm_debug_state_t)),
	                 THREAD_CHUNK * (sizeof(arm_debug_state_t)),
	                 "arm debug state");

	/*
	 * Create a zone for the user save state.  At the time this zone was created,
	 * the user save state was 848 bytes, and the matching kalloc zone was 1024
	 * bytes, which would result in significant amounts of wasted space if we
	 * simply used kalloc to allocate the user saved state.
	 *
	 * 0x4000 has been chosen as the allocation size, as it results in 272 bytes
	 * of wasted space per chunk, which should correspond to 19 allocations.
	 */
	user_ss_zone = zinit(sizeof(arm_context_t),
	                     CONFIG_THREAD_MAX * (sizeof(arm_context_t)),
	                     USER_SS_ZONE_ALLOC_SIZE,
	                     "user save state");
}