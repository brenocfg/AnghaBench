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
struct fasttime_t {scalar_t__ tv_usec; int /*<<< orphan*/  tv_jiff; } ;

/* Variables and functions */
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline int fasttime_cmp(struct fasttime_t *t0, struct fasttime_t *t1)
{
	/* Compare jiffies. Takes care of wrapping */
	if (time_before(t0->tv_jiff, t1->tv_jiff))
		return -1;
	else if (time_after(t0->tv_jiff, t1->tv_jiff))
		return 1;

	/* Compare us */
	if (t0->tv_usec < t1->tv_usec)
		return -1;
	else if (t0->tv_usec > t1->tv_usec)
		return 1;
	return 0;
}