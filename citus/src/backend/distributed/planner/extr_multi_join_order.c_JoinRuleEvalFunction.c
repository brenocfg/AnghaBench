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
typedef  int /*<<< orphan*/ * RuleEvalFunction ;
typedef  size_t JoinRuleType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 size_t CARTESIAN_PRODUCT ; 
 int /*<<< orphan*/  CartesianProduct ; 
 size_t DUAL_PARTITION_JOIN ; 
 int /*<<< orphan*/  DualPartitionJoin ; 
 size_t LOCAL_PARTITION_JOIN ; 
 int /*<<< orphan*/  LocalJoin ; 
 size_t REFERENCE_JOIN ; 
 int /*<<< orphan*/  ReferenceJoin ; 
 int /*<<< orphan*/ ** RuleEvalFunctionArray ; 
 size_t SINGLE_HASH_PARTITION_JOIN ; 
 size_t SINGLE_RANGE_PARTITION_JOIN ; 
 int /*<<< orphan*/  SinglePartitionJoin ; 

__attribute__((used)) static RuleEvalFunction
JoinRuleEvalFunction(JoinRuleType ruleType)
{
	static bool ruleEvalFunctionsInitialized = false;
	RuleEvalFunction ruleEvalFunction = NULL;

	if (!ruleEvalFunctionsInitialized)
	{
		RuleEvalFunctionArray[REFERENCE_JOIN] = &ReferenceJoin;
		RuleEvalFunctionArray[LOCAL_PARTITION_JOIN] = &LocalJoin;
		RuleEvalFunctionArray[SINGLE_RANGE_PARTITION_JOIN] = &SinglePartitionJoin;
		RuleEvalFunctionArray[SINGLE_HASH_PARTITION_JOIN] = &SinglePartitionJoin;
		RuleEvalFunctionArray[DUAL_PARTITION_JOIN] = &DualPartitionJoin;
		RuleEvalFunctionArray[CARTESIAN_PRODUCT] = &CartesianProduct;

		ruleEvalFunctionsInitialized = true;
	}

	ruleEvalFunction = RuleEvalFunctionArray[ruleType];
	Assert(ruleEvalFunction != NULL);

	return ruleEvalFunction;
}