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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KTIME_LOW_RES ; 
 struct timespec ktime_to_timespec (int /*<<< orphan*/ ) ; 

int posix_get_coarse_res(const clockid_t which_clock, struct timespec *tp)
{
	*tp = ktime_to_timespec(KTIME_LOW_RES);
	return 0;
}