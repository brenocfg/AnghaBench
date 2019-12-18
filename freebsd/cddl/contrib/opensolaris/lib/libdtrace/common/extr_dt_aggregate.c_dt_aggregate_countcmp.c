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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int DT_GREATERTHAN ; 
 int DT_LESSTHAN ; 

__attribute__((used)) static int
dt_aggregate_countcmp(int64_t *lhs, int64_t *rhs)
{
	int64_t lvar = *lhs;
	int64_t rvar = *rhs;

	if (lvar < rvar)
		return (DT_LESSTHAN);

	if (lvar > rvar)
		return (DT_GREATERTHAN);

	return (0);
}