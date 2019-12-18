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
 int dt_aggregate_varcmp (void const*,void const*) ; 

__attribute__((used)) static int
dt_aggregate_keyvarcmp(const void *lhs, const void *rhs)
{
	int rval;

	if ((rval = dt_aggregate_keycmp(lhs, rhs)) != 0)
		return (rval);

	return (dt_aggregate_varcmp(lhs, rhs));
}