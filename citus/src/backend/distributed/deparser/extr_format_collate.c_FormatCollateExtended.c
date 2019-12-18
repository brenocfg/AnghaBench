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
typedef  int bits16 ;
struct TYPE_2__ {int /*<<< orphan*/  collname; int /*<<< orphan*/  collnamespace; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__* Form_pg_collation ;

/* Variables and functions */
 int /*<<< orphan*/  COLLOID ; 
 scalar_t__ CollationIsVisible (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int FORMAT_COLLATE_ALLOW_INVALID ; 
 int FORMAT_COLLATE_FORCE_QUALIFY ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* get_namespace_name_or_temp (int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 char* quote_qualified_identifier (char*,char*) ; 

char *
FormatCollateExtended(Oid collid, bits16 flags)
{
	HeapTuple tuple = NULL;
	Form_pg_collation collform = NULL;
	char *buf = NULL;
	char *nspname = NULL;
	char *typname = NULL;

	if (collid == InvalidOid && (flags & FORMAT_COLLATE_ALLOW_INVALID) != 0)
	{
		return pstrdup("-");
	}

	tuple = SearchSysCache1(COLLOID, ObjectIdGetDatum(collid));
	if (!HeapTupleIsValid(tuple))
	{
		if ((flags & FORMAT_COLLATE_ALLOW_INVALID) != 0)
		{
			return pstrdup("???");
		}
		else
		{
			elog(ERROR, "cache lookup failed for collate %u", collid);
		}
	}
	collform = (Form_pg_collation) GETSTRUCT(tuple);

	if ((flags & FORMAT_COLLATE_FORCE_QUALIFY) == 0 && CollationIsVisible(collid))
	{
		nspname = NULL;
	}
	else
	{
		nspname = get_namespace_name_or_temp(collform->collnamespace);
	}

	typname = NameStr(collform->collname);

	buf = quote_qualified_identifier(nspname, typname);

	ReleaseSysCache(tuple);

	return buf;
}