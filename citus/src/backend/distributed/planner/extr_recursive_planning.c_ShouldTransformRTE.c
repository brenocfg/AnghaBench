#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ rtekind; scalar_t__ funcordinality; scalar_t__ lateral; } ;
typedef  TYPE_1__ RangeTblEntry ;

/* Variables and functions */
 scalar_t__ RTE_FUNCTION ; 

__attribute__((used)) static bool
ShouldTransformRTE(RangeTblEntry *rangeTableEntry)
{
	/*
	 * We should wrap only function rtes that are not LATERAL and
	 * without WITH ORDINALITY clause
	 */
	if (rangeTableEntry->rtekind != RTE_FUNCTION ||
		rangeTableEntry->lateral ||
		rangeTableEntry->funcordinality)
	{
		return false;
	}
	return true;
}