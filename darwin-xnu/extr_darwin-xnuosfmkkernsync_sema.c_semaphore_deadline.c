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
typedef  int uint64_t ;
typedef  scalar_t__ clock_res_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (scalar_t__,int*) ; 

__attribute__((used)) static __inline__ uint64_t
semaphore_deadline(
	unsigned int		sec,
	clock_res_t			nsec)
{
	uint64_t	abstime;

	nanoseconds_to_absolutetime((uint64_t)sec *	NSEC_PER_SEC + nsec, &abstime);
	clock_absolutetime_interval_to_deadline(abstime, &abstime);

	return (abstime);
}