#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nspowner; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_namespace ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserId () ; 
 char* GetUserNameFromId (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NAMESPACEOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
SchemaOwnerName(Oid objectId)
{
	HeapTuple tuple = NULL;
	Oid ownerId = InvalidOid;
	char *ownerName = NULL;

	tuple = SearchSysCache1(NAMESPACEOID, ObjectIdGetDatum(objectId));
	if (HeapTupleIsValid(tuple))
	{
		ownerId = ((Form_pg_namespace) GETSTRUCT(tuple))->nspowner;
	}
	else
	{
		ownerId = GetUserId();
	}

	ownerName = GetUserNameFromId(ownerId, false);

	ReleaseSysCache(tuple);

	return ownerName;
}