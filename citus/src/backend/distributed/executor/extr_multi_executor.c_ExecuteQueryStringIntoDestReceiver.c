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
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteQueryIntoDestReceiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseQueryString (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecuteQueryStringIntoDestReceiver(const char *queryString, ParamListInfo params,
								   DestReceiver *dest)
{
	Query *query = ParseQueryString(queryString, NULL, 0);

	ExecuteQueryIntoDestReceiver(query, params, dest);
}