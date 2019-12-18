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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int PVC_RECURSE_AGGREGATES ; 
 int PVC_RECURSE_WINDOWFUNCS ; 
 int /*<<< orphan*/ * pull_var_clause (int /*<<< orphan*/ *,int) ; 

List *
pull_var_clause_default(Node *node)
{
	/*
	 * PVC_REJECT_PLACEHOLDERS is implicit if PVC_INCLUDE_PLACEHOLDERS
	 * isn't specified.
	 */
	List *columnList = pull_var_clause(node, PVC_RECURSE_AGGREGATES |
									   PVC_RECURSE_WINDOWFUNCS);

	return columnList;
}