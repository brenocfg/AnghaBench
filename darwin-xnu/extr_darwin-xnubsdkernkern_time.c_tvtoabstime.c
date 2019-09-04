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
typedef  scalar_t__ uint64_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

uint64_t
tvtoabstime(
	struct timeval	*tvp)
{
	uint64_t	result, usresult;

	clock_interval_to_absolutetime_interval(
						tvp->tv_sec, NSEC_PER_SEC, &result);
	clock_interval_to_absolutetime_interval(
						tvp->tv_usec, NSEC_PER_USEC, &usresult);

	return (result + usresult);
}