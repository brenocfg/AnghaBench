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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  clock_sec_t ;
typedef  int /*<<< orphan*/  clock_nsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_get_boottime_nanotime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

time_t
boottime_sec(void)
{
	clock_sec_t		secs;
	clock_nsec_t	nanosecs;

	clock_get_boottime_nanotime(&secs, &nanosecs);
	return (secs);
}