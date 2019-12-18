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
struct TYPE_3__ {scalar_t__ aggdistinct; scalar_t__ aggorder; } ;
typedef  size_t AggregateType ;
typedef  TYPE_1__ Aggref ;

/* Variables and functions */
 char** AggregateNames ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 

__attribute__((used)) static void
ErrorIfUnsupportedJsonAggregate(AggregateType type,
								Aggref *aggregateExpression)
{
	/* if json aggregate has order by, we error out */
	if (aggregateExpression->aggorder)
	{
		const char *name = AggregateNames[type];
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("%s with order by is unsupported", name)));
	}

	/* if json aggregate has distinct, we error out */
	if (aggregateExpression->aggdistinct)
	{
		const char *name = AggregateNames[type];
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("%s (distinct) is unsupported", name)));
	}
}