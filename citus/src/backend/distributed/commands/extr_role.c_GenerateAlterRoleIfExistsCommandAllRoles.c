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
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_2__ {int /*<<< orphan*/  rolname; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  HeapScanDesc ;
typedef  TYPE_1__* Form_pg_authid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AuthIdRelationId ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 char* GenerateAlterRoleIfExistsCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsReservedName (char const*) ; 
 int /*<<< orphan*/ * NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

List *
GenerateAlterRoleIfExistsCommandAllRoles()
{
	Relation pgAuthId = heap_open(AuthIdRelationId, AccessShareLock);
	TupleDesc pgAuthIdDescription = RelationGetDescr(pgAuthId);
	HeapTuple tuple = NULL;
	List *commands = NIL;
	const char *alterRoleQuery = NULL;

#if PG_VERSION_NUM >= 120000
	TableScanDesc scan = table_beginscan_catalog(pgAuthId, 0, NULL);
#else
	HeapScanDesc scan = heap_beginscan_catalog(pgAuthId, 0, NULL);
#endif

	while ((tuple = heap_getnext(scan, ForwardScanDirection)) != NULL)
	{
		const char *rolename = NameStr(((Form_pg_authid) GETSTRUCT(tuple))->rolname);

		/*
		 * The default roles are skipped, because reserved roles
		 * cannot be altered.
		 */
		if (IsReservedName(rolename))
		{
			continue;
		}
		alterRoleQuery = GenerateAlterRoleIfExistsCommand(tuple, pgAuthIdDescription);
		commands = lappend(commands, (void *) alterRoleQuery);
	}

	heap_endscan(scan);
	heap_close(pgAuthId, AccessShareLock);

	return commands;
}