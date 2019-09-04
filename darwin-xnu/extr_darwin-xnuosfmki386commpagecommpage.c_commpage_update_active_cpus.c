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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE32_BASE_ADDRESS ; 
 scalar_t__ _COMM_PAGE32_START_ADDRESS ; 
 scalar_t__ _COMM_PAGE_ACTIVE_CPUS ; 
 char* commPagePtr32 ; 
 char* commPagePtr64 ; 
 int /*<<< orphan*/  commpage_active_cpus_lock ; 
 scalar_t__ processor_avail_count ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
commpage_update_active_cpus(void)
{
	char	    *cp;
	volatile uint8_t    *ip;
	
	/* At least 32-bit commpage must be initialized */
	if (!commPagePtr32)
		return;

	simple_lock(&commpage_active_cpus_lock);

	cp = commPagePtr32;
	cp += (_COMM_PAGE_ACTIVE_CPUS - _COMM_PAGE32_BASE_ADDRESS);
	ip = (volatile uint8_t*) cp;
	*ip = (uint8_t) processor_avail_count;
	
	cp = commPagePtr64;
	if ( cp ) {
		cp += (_COMM_PAGE_ACTIVE_CPUS - _COMM_PAGE32_START_ADDRESS);
		ip = (volatile uint8_t*) cp;
		*ip = (uint8_t) processor_avail_count;
	}

	simple_unlock(&commpage_active_cpus_lock);
}