#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ colname; int /*<<< orphan*/  is_not_null; int /*<<< orphan*/  typeName; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ColumnDef ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* FormatCollateBEQualified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetColumnDefCollation (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LookupTypeNameOid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 char const* format_type_be_qualified (int /*<<< orphan*/ ) ; 
 char const* quote_identifier (scalar_t__) ; 

__attribute__((used)) static void
AppendColumnDef(StringInfo str, ColumnDef *columnDef)
{
	Oid typeOid = LookupTypeNameOid(NULL, columnDef->typeName, false);
	Oid collationOid = GetColumnDefCollation(NULL, columnDef, typeOid);

	Assert(!columnDef->is_not_null); /* not null is not supported on composite types */

	if (columnDef->colname)
	{
		appendStringInfo(str, "%s ", quote_identifier(columnDef->colname));
	}

	appendStringInfo(str, "%s", format_type_be_qualified(typeOid));

	if (OidIsValid(collationOid))
	{
		const char *identifier = FormatCollateBEQualified(collationOid);
		appendStringInfo(str, " COLLATE %s", identifier);
	}
}