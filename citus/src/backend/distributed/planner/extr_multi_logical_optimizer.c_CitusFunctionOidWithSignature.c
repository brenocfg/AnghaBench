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
struct TYPE_3__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  args; struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* FuncnameGetCandidates (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Oid
CitusFunctionOidWithSignature(char *functionName, int numargs, Oid *argtypes)
{
	List *aggregateName = list_make2(makeString("citus"), makeString(functionName));
	FuncCandidateList clist = FuncnameGetCandidates(aggregateName, numargs, NIL, false,
													false, true);

	for (; clist; clist = clist->next)
	{
		if (memcmp(clist->args, argtypes, numargs * sizeof(Oid)) == 0)
		{
			return clist->oid;
		}
	}

	ereport(ERROR, (errmsg("no matching oid for function: %s", functionName)));
	return InvalidOid;
}