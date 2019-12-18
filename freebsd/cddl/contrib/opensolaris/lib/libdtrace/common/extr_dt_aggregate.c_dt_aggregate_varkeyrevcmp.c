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
 int dt_aggregate_varkeycmp (void const*,void const*) ; 

__attribute__((used)) static int
dt_aggregate_varkeyrevcmp(const void *lhs, const void *rhs)
{
	return (dt_aggregate_varkeycmp(rhs, lhs));
}