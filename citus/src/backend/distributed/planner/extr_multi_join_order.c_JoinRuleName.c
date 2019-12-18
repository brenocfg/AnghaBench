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
typedef  size_t JoinRuleType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 size_t CARTESIAN_PRODUCT ; 
 size_t DUAL_PARTITION_JOIN ; 
 size_t LOCAL_PARTITION_JOIN ; 
 size_t REFERENCE_JOIN ; 
 char** RuleNameArray ; 
 size_t SINGLE_HASH_PARTITION_JOIN ; 
 size_t SINGLE_RANGE_PARTITION_JOIN ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
JoinRuleName(JoinRuleType ruleType)
{
	static bool ruleNamesInitialized = false;
	char *ruleName = NULL;

	if (!ruleNamesInitialized)
	{
		/* use strdup() to be independent of memory contexts */
		RuleNameArray[REFERENCE_JOIN] = strdup("reference join");
		RuleNameArray[LOCAL_PARTITION_JOIN] = strdup("local partition join");
		RuleNameArray[SINGLE_HASH_PARTITION_JOIN] =
			strdup("single hash partition join");
		RuleNameArray[SINGLE_RANGE_PARTITION_JOIN] =
			strdup("single range partition join");
		RuleNameArray[DUAL_PARTITION_JOIN] = strdup("dual partition join");
		RuleNameArray[CARTESIAN_PRODUCT] = strdup("cartesian product");

		ruleNamesInitialized = true;
	}

	ruleName = RuleNameArray[ruleType];
	Assert(ruleName != NULL);

	return ruleName;
}