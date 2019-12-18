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
typedef  int /*<<< orphan*/ * RuleApplyFunction ;
typedef  size_t JoinRuleType ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyCartesianProduct ; 
 int /*<<< orphan*/  ApplyDualPartitionJoin ; 
 int /*<<< orphan*/  ApplyLocalJoin ; 
 int /*<<< orphan*/  ApplyReferenceJoin ; 
 int /*<<< orphan*/  ApplySingleHashPartitionJoin ; 
 int /*<<< orphan*/  ApplySingleRangePartitionJoin ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 size_t CARTESIAN_PRODUCT ; 
 size_t DUAL_PARTITION_JOIN ; 
 size_t LOCAL_PARTITION_JOIN ; 
 size_t REFERENCE_JOIN ; 
 int /*<<< orphan*/ ** RuleApplyFunctionArray ; 
 size_t SINGLE_HASH_PARTITION_JOIN ; 
 size_t SINGLE_RANGE_PARTITION_JOIN ; 

__attribute__((used)) static RuleApplyFunction
JoinRuleApplyFunction(JoinRuleType ruleType)
{
	static bool ruleApplyFunctionInitialized = false;
	RuleApplyFunction ruleApplyFunction = NULL;

	if (!ruleApplyFunctionInitialized)
	{
		RuleApplyFunctionArray[REFERENCE_JOIN] = &ApplyReferenceJoin;
		RuleApplyFunctionArray[LOCAL_PARTITION_JOIN] = &ApplyLocalJoin;
		RuleApplyFunctionArray[SINGLE_HASH_PARTITION_JOIN] =
			&ApplySingleHashPartitionJoin;
		RuleApplyFunctionArray[SINGLE_RANGE_PARTITION_JOIN] =
			&ApplySingleRangePartitionJoin;
		RuleApplyFunctionArray[DUAL_PARTITION_JOIN] = &ApplyDualPartitionJoin;
		RuleApplyFunctionArray[CARTESIAN_PRODUCT] = &ApplyCartesianProduct;

		ruleApplyFunctionInitialized = true;
	}

	ruleApplyFunction = RuleApplyFunctionArray[ruleType];
	Assert(ruleApplyFunction != NULL);

	return ruleApplyFunction;
}