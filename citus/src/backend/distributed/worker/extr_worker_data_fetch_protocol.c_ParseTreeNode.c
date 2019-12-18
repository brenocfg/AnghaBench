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
struct TYPE_2__ {int /*<<< orphan*/ * stmt; } ;
typedef  TYPE_1__ RawStmt ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * ParseTreeRawStmt (char const*) ; 

Node *
ParseTreeNode(const char *ddlCommand)
{
	Node *parseTreeNode = ParseTreeRawStmt(ddlCommand);

	parseTreeNode = ((RawStmt *) parseTreeNode)->stmt;

	return parseTreeNode;
}