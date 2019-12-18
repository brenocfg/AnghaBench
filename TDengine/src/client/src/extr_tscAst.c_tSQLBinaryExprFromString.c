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
struct TYPE_4__ {scalar_t__ nodeType; int /*<<< orphan*/ * pExpr; } ;
typedef  TYPE_1__ tSQLSyntaxNode ;
typedef  int /*<<< orphan*/  tSQLBinaryExpr ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  SSchema ;

/* Variables and functions */
 scalar_t__ TSQL_NODE_EXPR ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* createSyntaxTree (int /*<<< orphan*/ *,scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void tSQLBinaryExprFromString(tSQLBinaryExpr **pExpr, SSchema *pSchema, int32_t numOfCols, char *src, int32_t len) {
  *pExpr = NULL;
  if (len <= 0 || src == NULL || pSchema == NULL || numOfCols <= 0) {
    return;
  }

  int32_t         pos = 0;
  tSQLSyntaxNode *pStxNode = createSyntaxTree(pSchema, numOfCols, src, &pos);
  if (pStxNode != NULL) {
    assert(pStxNode->nodeType == TSQL_NODE_EXPR);
    *pExpr = pStxNode->pExpr;
    free(pStxNode);
  }
}