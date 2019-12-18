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
struct TYPE_2__ {scalar_t__ workerHashFunctionId; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ FunctionOid (char*,char*,int const) ; 
 scalar_t__ InvalidOid ; 
 TYPE_1__ MetadataCache ; 
 scalar_t__ get_extension_oid (char*,int) ; 
 scalar_t__ get_extension_schema (scalar_t__) ; 
 char* get_namespace_name (scalar_t__) ; 

Oid
CitusWorkerHashFunctionId(void)
{
	if (MetadataCache.workerHashFunctionId == InvalidOid)
	{
		Oid citusExtensionOid = get_extension_oid("citus", false);
		Oid citusSchemaOid = get_extension_schema(citusExtensionOid);
		char *citusSchemaName = get_namespace_name(citusSchemaOid);
		const int argCount = 1;

		MetadataCache.workerHashFunctionId =
			FunctionOid(citusSchemaName, "worker_hash", argCount);
	}

	return MetadataCache.workerHashFunctionId;
}