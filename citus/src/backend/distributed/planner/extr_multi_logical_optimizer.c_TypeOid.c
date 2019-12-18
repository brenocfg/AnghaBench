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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_type_oid ; 
 int /*<<< orphan*/  GetSysCacheOid2Compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 

__attribute__((used)) static Oid
TypeOid(Oid schemaId, const char *typeName)
{
	Oid typeOid;

	typeOid = GetSysCacheOid2Compat(TYPENAMENSP, Anum_pg_type_oid,
									PointerGetDatum(typeName),
									ObjectIdGetDatum(schemaId));

	return typeOid;
}