#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nSQLOptr; struct TYPE_5__* pRight; struct TYPE_5__* pLeft; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ TK_PLUS ; 
 scalar_t__ TK_REM ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  optrToString (TYPE_1__*,char**) ; 
 scalar_t__ tSQLExprNodeToString (TYPE_1__*,char**) ; 

int32_t buildArithmeticExprString(tSQLExpr* pExpr, char** exprString) {
  tSQLExpr* pLeft = pExpr->pLeft;
  tSQLExpr* pRight = pExpr->pRight;

  *(*exprString) = '(';
  *exprString += 1;

  if (pLeft->nSQLOptr >= TK_PLUS && pLeft->nSQLOptr <= TK_REM) {
    buildArithmeticExprString(pLeft, exprString);
  } else {
    int32_t ret = tSQLExprNodeToString(pLeft, exprString);
    if (ret != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }
  }

  optrToString(pExpr, exprString);

  if (pRight->nSQLOptr >= TK_PLUS && pRight->nSQLOptr <= TK_REM) {
    buildArithmeticExprString(pRight, exprString);
  } else {
    int32_t ret = tSQLExprNodeToString(pRight, exprString);
    if (ret != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }
  }

  *(*exprString) = ')';
  *exprString += 1;

  return TSDB_CODE_SUCCESS;
}