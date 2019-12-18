#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  compareIntervalFunctionCall; } ;
struct TYPE_18__ {TYPE_5__* lessConsts; TYPE_4__* lessEqualConsts; TYPE_3__* greaterConsts; TYPE_2__* greaterEqualConsts; TYPE_1__* equalConsts; } ;
struct TYPE_17__ {int /*<<< orphan*/  minValue; int /*<<< orphan*/  maxValue; int /*<<< orphan*/  maxValueExists; int /*<<< orphan*/  minValueExists; } ;
struct TYPE_16__ {int /*<<< orphan*/  constvalue; } ;
struct TYPE_15__ {int /*<<< orphan*/  constvalue; } ;
struct TYPE_14__ {int /*<<< orphan*/  constvalue; } ;
struct TYPE_13__ {int /*<<< orphan*/  constvalue; } ;
struct TYPE_12__ {int /*<<< orphan*/  constvalue; } ;
typedef  TYPE_6__ ShardInterval ;
typedef  TYPE_7__ PruningInstance ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_8__ ClauseWalkerContext ;

/* Variables and functions */
 scalar_t__ PerformValueCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ExhaustivePruneOne(ShardInterval *curInterval,
				   ClauseWalkerContext *context,
				   PruningInstance *prune)
{
	FunctionCallInfo compareFunctionCall = (FunctionCallInfo) &
										   context->compareIntervalFunctionCall;
	Datum compareWith = 0;

	/* NULL boundaries can't be compared to */
	if (!curInterval->minValueExists || !curInterval->maxValueExists)
	{
		return false;
	}

	if (prune->equalConsts)
	{
		compareWith = prune->equalConsts->constvalue;

		if (PerformValueCompare(compareFunctionCall,
								compareWith,
								curInterval->minValue) < 0)
		{
			return true;
		}

		if (PerformValueCompare(compareFunctionCall,
								compareWith,
								curInterval->maxValue) > 0)
		{
			return true;
		}
	}
	if (prune->greaterEqualConsts)
	{
		compareWith = prune->greaterEqualConsts->constvalue;

		if (PerformValueCompare(compareFunctionCall,
								curInterval->maxValue,
								compareWith) < 0)
		{
			return true;
		}
	}
	if (prune->greaterConsts)
	{
		compareWith = prune->greaterConsts->constvalue;

		if (PerformValueCompare(compareFunctionCall,
								curInterval->maxValue,
								compareWith) <= 0)
		{
			return true;
		}
	}
	if (prune->lessEqualConsts)
	{
		compareWith = prune->lessEqualConsts->constvalue;

		if (PerformValueCompare(compareFunctionCall,
								curInterval->minValue,
								compareWith) > 0)
		{
			return true;
		}
	}
	if (prune->lessConsts)
	{
		compareWith = prune->lessConsts->constvalue;

		if (PerformValueCompare(compareFunctionCall,
								curInterval->minValue,
								compareWith) >= 0)
		{
			return true;
		}
	}

	return false;
}