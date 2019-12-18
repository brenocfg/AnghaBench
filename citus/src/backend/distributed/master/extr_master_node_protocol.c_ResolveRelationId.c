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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * textToQualifiedNameList (int /*<<< orphan*/ *) ; 

Oid
ResolveRelationId(text *relationName, bool missingOk)
{
	List *relationNameList = NIL;
	RangeVar *relation = NULL;
	Oid relationId = InvalidOid;

	/* resolve relationId from passed in schema and relation name */
	relationNameList = textToQualifiedNameList(relationName);
	relation = makeRangeVarFromNameList(relationNameList);
	relationId = RangeVarGetRelid(relation, NoLock, missingOk);

	return relationId;
}