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
typedef  int /*<<< orphan*/  u_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u_int64_t
pktsched_nsecs_to_abstime(u_int64_t nsecs)
{
	u_int64_t abstime;

	nanoseconds_to_absolutetime(nsecs, &abstime);
	return (abstime);
}