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
struct TYPE_2__ {scalar_t__ copyFormatTypeId; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_enum_oid ; 
 scalar_t__ GetSysCacheOid2Compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 TYPE_1__ MetadataCache ; 
 int /*<<< orphan*/  PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 

Oid
CitusCopyFormatTypeId(void)
{
	if (MetadataCache.copyFormatTypeId == InvalidOid)
	{
		char *typeName = "citus_copy_format";
		MetadataCache.copyFormatTypeId = GetSysCacheOid2Compat(TYPENAMENSP,
															   Anum_pg_enum_oid,
															   PointerGetDatum(typeName),
															   PG_CATALOG_NAMESPACE);
	}

	return MetadataCache.copyFormatTypeId;
}