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
typedef  int /*<<< orphan*/  dtrace_aggdata_t ;

/* Variables and functions */
 int DTRACE_AGGWALK_NEXT ; 

__attribute__((used)) static int
count_aggregate(const dtrace_aggdata_t *agg, void *arg)
{
	*((size_t *)arg) += 1;

	return (DTRACE_AGGWALK_NEXT);
}