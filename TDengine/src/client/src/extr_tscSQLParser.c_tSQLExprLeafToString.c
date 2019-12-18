#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pRight; struct TYPE_6__* pLeft; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  isExprDirectParentOfLeaftNode (TYPE_1__*) ; 
 scalar_t__ optrToString (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  tSQLExprNodeToString (TYPE_1__*,char**) ; 

__attribute__((used)) static int32_t tSQLExprLeafToString(tSQLExpr* pExpr, bool addParentheses, char** output) {
  if (!isExprDirectParentOfLeaftNode(pExpr)) {
    return TSDB_CODE_INVALID_SQL;
  }

  tSQLExpr* pLeft = pExpr->pLeft;
  tSQLExpr* pRight = pExpr->pRight;

  if (addParentheses) {
    *(*output) = '(';
    *output += 1;
  }

  tSQLExprNodeToString(pLeft, output);
  if (optrToString(pExpr, output) != TSDB_CODE_SUCCESS) {
    return TSDB_CODE_INVALID_SQL;
  }

  tSQLExprNodeToString(pRight, output);

  if (addParentheses) {
    *(*output) = ')';
    *output += 1;
  }

  return TSDB_CODE_SUCCESS;
}