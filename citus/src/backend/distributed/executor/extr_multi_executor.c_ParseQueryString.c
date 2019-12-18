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
typedef  int /*<<< orphan*/  RawStmt ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ParseTreeRawStmt (char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_analyze_and_rewrite (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

Query *
ParseQueryString(const char *queryString, Oid *paramOids, int numParams)
{
	Query *query = NULL;
	RawStmt *rawStmt = (RawStmt *) ParseTreeRawStmt(queryString);
	List *queryTreeList =
		pg_analyze_and_rewrite(rawStmt, queryString, paramOids, numParams, NULL);

	if (list_length(queryTreeList) != 1)
	{
		ereport(ERROR, (errmsg("can only execute a single query")));
	}

	query = (Query *) linitial(queryTreeList);

	return query;
}