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
typedef  int int64_t ;

/* Variables and functions */
 int DT_GREATERTHAN ; 
 int DT_LESSTHAN ; 

__attribute__((used)) static int
dt_aggregate_averagecmp(int64_t *lhs, int64_t *rhs)
{
	int64_t lavg = lhs[0] ? (lhs[1] / lhs[0]) : 0;
	int64_t ravg = rhs[0] ? (rhs[1] / rhs[0]) : 0;

	if (lavg < ravg)
		return (DT_LESSTHAN);

	if (lavg > ravg)
		return (DT_GREATERTHAN);

	return (0);
}