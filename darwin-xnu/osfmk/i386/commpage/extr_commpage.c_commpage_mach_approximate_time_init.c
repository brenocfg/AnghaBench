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
typedef  int uint8_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE32_BASE_ADDRESS ; 
 scalar_t__ _COMM_PAGE32_START_ADDRESS ; 
 scalar_t__ _COMM_PAGE_APPROX_TIME_SUPPORTED ; 
 char* commPagePtr32 ; 
 char* commPagePtr64 ; 
 int /*<<< orphan*/  commpage_update_mach_approximate_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
commpage_mach_approximate_time_init(void)
{
	char *cp = commPagePtr32;
	uint8_t supported;

#ifdef CONFIG_MACH_APPROXIMATE_TIME
	supported = 1;
#else
	supported = 0;
#endif
	if ( cp ) {
		cp += (_COMM_PAGE_APPROX_TIME_SUPPORTED - _COMM_PAGE32_BASE_ADDRESS);
		*(boolean_t *)cp = supported;
	}
	
	cp = commPagePtr64;
	if ( cp ) {
		cp += (_COMM_PAGE_APPROX_TIME_SUPPORTED - _COMM_PAGE32_START_ADDRESS);
		*(boolean_t *)cp = supported;
	}
	commpage_update_mach_approximate_time(0);
}