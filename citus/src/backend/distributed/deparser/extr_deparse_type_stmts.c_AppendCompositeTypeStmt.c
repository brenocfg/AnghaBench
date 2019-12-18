#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  coldeflist; TYPE_1__* typevar; } ;
struct TYPE_4__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  schemaname; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ CompositeTypeStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AppendColumnDefList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,...) ; 
 char* quote_qualified_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppendCompositeTypeStmt(StringInfo str, CompositeTypeStmt *stmt)
{
	const char *identifier = quote_qualified_identifier(stmt->typevar->schemaname,
														stmt->typevar->relname);
	appendStringInfo(str, "CREATE TYPE %s AS (", identifier);
	AppendColumnDefList(str, stmt->coldeflist);
	appendStringInfo(str, ");");
}