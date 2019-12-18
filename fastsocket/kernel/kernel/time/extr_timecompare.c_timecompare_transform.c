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
typedef  scalar_t__ u64 ;
struct timecompare {int skew; scalar_t__ last_update; scalar_t__ offset; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int TIMECOMPARE_SKEW_RESOLUTION ; 
 int /*<<< orphan*/  ns_to_ktime (scalar_t__) ; 

ktime_t timecompare_transform(struct timecompare *sync,
			      u64 source_tstamp)
{
	u64 nsec;

	nsec = source_tstamp + sync->offset;
	nsec += (s64)(source_tstamp - sync->last_update) * sync->skew /
		TIMECOMPARE_SKEW_RESOLUTION;

	return ns_to_ktime(nsec);
}