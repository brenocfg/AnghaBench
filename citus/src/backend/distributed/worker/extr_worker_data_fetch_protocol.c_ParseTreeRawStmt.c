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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char const*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ check_log_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhidestmt (int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_parse_query (char const*) ; 

Node *
ParseTreeRawStmt(const char *ddlCommand)
{
	Node *parseTreeNode = NULL;
	List *parseTreeList = NULL;
	uint32 parseTreeCount = 0;

	parseTreeList = pg_parse_query(ddlCommand);

	/* log immediately if dictated by log statement */
	if (check_log_statement(parseTreeList))
	{
		ereport(LOG, (errmsg("statement: %s", ApplyLogRedaction(ddlCommand)),
					  errhidestmt(true)));
	}

	parseTreeCount = list_length(parseTreeList);
	if (parseTreeCount != 1)
	{
		ereport(ERROR, (errmsg("cannot execute multiple utility events")));
	}

	/*
	 * xact.c rejects certain commands that are unsafe to run inside transaction
	 * blocks. Since we only apply commands that relate to creating tables and
	 * those commands are safe, we can safely set the ProcessUtilityContext to
	 * PROCESS_UTILITY_TOPLEVEL.
	 */
	parseTreeNode = (Node *) linitial(parseTreeList);

	return parseTreeNode;
}