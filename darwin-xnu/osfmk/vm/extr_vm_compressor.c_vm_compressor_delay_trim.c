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
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;

/* Variables and functions */
 scalar_t__ DELAY_TRIM_ON_WAKE_SECS ; 
 int /*<<< orphan*/  clock_get_system_nanotime (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dont_trim_until_ts ; 

void
vm_compressor_delay_trim(void)
{
        clock_sec_t	sec;
	clock_nsec_t	nsec;

	clock_get_system_nanotime(&sec, &nsec);
	dont_trim_until_ts = sec + DELAY_TRIM_ON_WAKE_SECS;
}