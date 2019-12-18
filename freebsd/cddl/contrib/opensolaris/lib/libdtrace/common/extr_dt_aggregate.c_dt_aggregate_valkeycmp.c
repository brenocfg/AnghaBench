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

/* Variables and functions */
 int dt_aggregate_keycmp (void const*,void const*) ; 
 int dt_aggregate_valcmp (void const*,void const*) ; 

__attribute__((used)) static int
dt_aggregate_valkeycmp(const void *lhs, const void *rhs)
{
	int rval;

	if ((rval = dt_aggregate_valcmp(lhs, rhs)) != 0)
		return (rval);

	/*
	 * If we're here, the values for the two aggregation elements are
	 * equal.  We already know that the key layout is the same for the two
	 * elements; we must now compare the keys themselves as a tie-breaker.
	 */
	return (dt_aggregate_keycmp(lhs, rhs));
}