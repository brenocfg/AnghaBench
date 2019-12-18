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
struct TYPE_2__ {int /*<<< orphan*/  typnamespace; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_type_oid ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  get_catalog_object_by_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
TypeOidGetNamespaceOid(Oid typeOid)
{
	Form_pg_type typeData = NULL;
	Relation catalog = heap_open(TypeRelationId, AccessShareLock);
#if PG_VERSION_NUM >= 120000
	HeapTuple typeTuple = get_catalog_object_by_oid(catalog, Anum_pg_type_oid, typeOid);
#else
	HeapTuple typeTuple = get_catalog_object_by_oid(catalog, typeOid);
#endif
	heap_close(catalog, AccessShareLock);

	typeData = (Form_pg_type) GETSTRUCT(typeTuple);

	return typeData->typnamespace;
}