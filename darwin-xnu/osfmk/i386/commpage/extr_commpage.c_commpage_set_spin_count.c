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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE32_BASE_ADDRESS ; 
 scalar_t__ _COMM_PAGE32_START_ADDRESS ; 
 scalar_t__ _COMM_PAGE_SPIN_COUNT ; 
 char* commPagePtr32 ; 
 char* commPagePtr64 ; 

void
commpage_set_spin_count(
	unsigned int 	count )
{
	char	    *cp;
	uint32_t    *ip;
	
	if (count == 0)	    /* we test for 0 after decrement, not before */
	    count = 1;
	    
	cp = commPagePtr32;
	if ( cp ) {
		cp += (_COMM_PAGE_SPIN_COUNT - _COMM_PAGE32_BASE_ADDRESS);
		ip = (uint32_t*) (void *) cp;
		*ip = (uint32_t) count;
	}
	
	cp = commPagePtr64;
	if ( cp ) {
		cp += (_COMM_PAGE_SPIN_COUNT - _COMM_PAGE32_START_ADDRESS);
		ip = (uint32_t*) (void *) cp;
		*ip = (uint32_t) count;
	}

}