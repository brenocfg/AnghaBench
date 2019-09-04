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
typedef  scalar_t__ clock_usec_t ;
typedef  int clock_sec_t ;

/* Variables and functions */
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  clock_get_boottime_microtime (int*,scalar_t__*) ; 
 int /*<<< orphan*/  commpage_update_boottime (scalar_t__) ; 

__attribute__((used)) static void
commpage_boottime_init(void)
{
	clock_sec_t secs;
	clock_usec_t microsecs;
	clock_get_boottime_microtime(&secs, &microsecs);
	commpage_update_boottime(secs * USEC_PER_SEC + microsecs);
}