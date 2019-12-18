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
struct TYPE_3__ {int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; int /*<<< orphan*/  maxValueExists; int /*<<< orphan*/  minValueExists; int /*<<< orphan*/  valueTypeId; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_1__ ShardInterval ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * makeStringInfo () ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static StringInfo
FragmentIntervalString(ShardInterval *fragmentInterval)
{
	StringInfo fragmentIntervalString = NULL;
	Oid typeId = fragmentInterval->valueTypeId;
	Oid outputFunctionId = InvalidOid;
	bool typeVariableLength = false;
	FmgrInfo *outputFunction = NULL;
	char *minValueString = NULL;
	char *maxValueString = NULL;

	Assert(fragmentInterval->minValueExists);
	Assert(fragmentInterval->maxValueExists);

	outputFunction = (FmgrInfo *) palloc0(sizeof(FmgrInfo));
	getTypeOutputInfo(typeId, &outputFunctionId, &typeVariableLength);
	fmgr_info(outputFunctionId, outputFunction);

	minValueString = OutputFunctionCall(outputFunction, fragmentInterval->minValue);
	maxValueString = OutputFunctionCall(outputFunction, fragmentInterval->maxValue);

	fragmentIntervalString = makeStringInfo();
	appendStringInfo(fragmentIntervalString, "[%s,%s]", minValueString, maxValueString);

	return fragmentIntervalString;
}