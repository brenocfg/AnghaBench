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
struct TYPE_2__ {scalar_t__ pgTableIsVisibleFuncId; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ FunctionOid (char*,char*,int const) ; 
 scalar_t__ InvalidOid ; 
 TYPE_1__ MetadataCache ; 

Oid
PgTableVisibleFuncId(void)
{
	if (MetadataCache.pgTableIsVisibleFuncId == InvalidOid)
	{
		const int argCount = 1;

		MetadataCache.pgTableIsVisibleFuncId =
			FunctionOid("pg_catalog", "pg_table_is_visible", argCount);
	}

	return MetadataCache.pgTableIsVisibleFuncId;
}