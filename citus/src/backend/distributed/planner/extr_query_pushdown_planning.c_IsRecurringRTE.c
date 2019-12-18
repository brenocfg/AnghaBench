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
typedef  int /*<<< orphan*/  RecurringTuplesType ;
typedef  int /*<<< orphan*/  RangeTblEntry ;

/* Variables and functions */
 int IsRecurringRangeTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
IsRecurringRTE(RangeTblEntry *rangeTableEntry, RecurringTuplesType *recurType)
{
	return IsRecurringRangeTable(list_make1(rangeTableEntry), recurType);
}