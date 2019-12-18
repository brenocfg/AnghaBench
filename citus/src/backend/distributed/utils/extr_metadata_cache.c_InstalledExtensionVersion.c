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
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_extension_extname ; 
 int Anum_pg_extension_extversion ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExtensionNameIndexId ; 
 int /*<<< orphan*/  ExtensionRelationId ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeCaches () ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MetadataCacheMemoryContext ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 
 char* text_to_cstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
InstalledExtensionVersion(void)
{
	Relation relation = NULL;
	SysScanDesc scandesc;
	ScanKeyData entry[1];
	HeapTuple extensionTuple = NULL;
	char *installedExtensionVersion = NULL;

	InitializeCaches();

	relation = heap_open(ExtensionRelationId, AccessShareLock);

	ScanKeyInit(&entry[0], Anum_pg_extension_extname, BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum("citus"));

	scandesc = systable_beginscan(relation, ExtensionNameIndexId, true,
								  NULL, 1, entry);

	extensionTuple = systable_getnext(scandesc);

	/* We assume that there can be at most one matching tuple */
	if (HeapTupleIsValid(extensionTuple))
	{
		MemoryContext oldMemoryContext = NULL;
		int extensionIndex = Anum_pg_extension_extversion;
		TupleDesc tupleDescriptor = RelationGetDescr(relation);
		bool isNull = false;

		Datum installedVersion = heap_getattr(extensionTuple, extensionIndex,
											  tupleDescriptor, &isNull);

		if (isNull)
		{
			ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
							errmsg("citus extension version is null")));
		}

		/* we will cache the result of citus version to prevent catalog access */
		oldMemoryContext = MemoryContextSwitchTo(MetadataCacheMemoryContext);

		installedExtensionVersion = text_to_cstring(DatumGetTextPP(installedVersion));

		MemoryContextSwitchTo(oldMemoryContext);
	}
	else
	{
		ereport(ERROR, (errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						errmsg("citus extension is not loaded")));
	}

	systable_endscan(scandesc);

	heap_close(relation, AccessShareLock);

	return installedExtensionVersion;
}