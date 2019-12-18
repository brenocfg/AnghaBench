#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  enumlabel; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/ * SysScanDesc ;
typedef  TYPE_1__ ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_enum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_enum_enumtypid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  EnumRelationId ; 
 int /*<<< orphan*/  EnumTypIdSortOrderIndexId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
EnumValsList(Oid typeOid)
{
	Relation enum_rel = NULL;
	SysScanDesc enum_scan = NULL;
	HeapTuple enum_tuple = NULL;
	ScanKeyData skey = { 0 };

	List *vals = NIL;

	/* Scan pg_enum for the members of the target enum type. */
	ScanKeyInit(&skey,
				Anum_pg_enum_enumtypid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(typeOid));

	enum_rel = heap_open(EnumRelationId, AccessShareLock);
	enum_scan = systable_beginscan(enum_rel,
								   EnumTypIdSortOrderIndexId,
								   true, NULL,
								   1, &skey);

	/* collect all value names in CREATE TYPE ... AS ENUM stmt */
	while (HeapTupleIsValid(enum_tuple = systable_getnext(enum_scan)))
	{
		Form_pg_enum en = (Form_pg_enum) GETSTRUCT(enum_tuple);
		vals = lappend(vals, makeString(pstrdup(NameStr(en->enumlabel))));
	}

	systable_endscan(enum_scan);
	heap_close(enum_rel, AccessShareLock);
	return vals;
}