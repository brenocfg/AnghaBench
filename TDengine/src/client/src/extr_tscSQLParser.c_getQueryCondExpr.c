#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nSQLOptr; struct TYPE_8__* pRight; struct TYPE_8__* pLeft; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  int /*<<< orphan*/  SCondExpr ;

/* Variables and functions */
 scalar_t__ TK_OR ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSQL_EXPR_TAG ; 
 scalar_t__ TSQL_EXPR_TBNAME ; 
 int /*<<< orphan*/  exchangeExpr (TYPE_1__*) ; 
 scalar_t__ handleExprInQueryCond (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  isExprDirectParentOfLeaftNode (TYPE_1__*) ; 
 int /*<<< orphan*/  isValidExpr (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 

int32_t getQueryCondExpr(SSqlCmd* pCmd, tSQLExpr** pExpr, SCondExpr* pCondExpr, int32_t* type, int32_t parentOptr) {
  if (pExpr == NULL) {
    return TSDB_CODE_SUCCESS;
  }

  const char* msg1 = "query condition between different columns must use 'AND'";

  tSQLExpr* pLeft = (*pExpr)->pLeft;
  tSQLExpr* pRight = (*pExpr)->pRight;

  if (!isValidExpr(pLeft, pRight, (*pExpr)->nSQLOptr)) {
    return TSDB_CODE_INVALID_SQL;
  }

  int32_t leftType = -1;
  int32_t rightType = -1;

  if (!isExprDirectParentOfLeaftNode(*pExpr)) {
    int32_t ret = getQueryCondExpr(pCmd, &(*pExpr)->pLeft, pCondExpr, &leftType, (*pExpr)->nSQLOptr);
    if (ret != TSDB_CODE_SUCCESS) {
      return ret;
    }

    ret = getQueryCondExpr(pCmd, &(*pExpr)->pRight, pCondExpr, &rightType, (*pExpr)->nSQLOptr);
    if (ret != TSDB_CODE_SUCCESS) {
      return ret;
    }

    /*
     *  if left child and right child do not belong to the same group, the sub
     *  expression is not valid for parent node, it must be TK_AND operator.
     */
    if (leftType != rightType) {
      if ((*pExpr)->nSQLOptr == TK_OR && (leftType + rightType != TSQL_EXPR_TBNAME + TSQL_EXPR_TAG)) {
        setErrMsg(pCmd, msg1);
        return TSDB_CODE_INVALID_SQL;
      }
    }

    *type = rightType;
    return TSDB_CODE_SUCCESS;
  }

  exchangeExpr(*pExpr);

  return handleExprInQueryCond(pCmd, pExpr, pCondExpr, type, parentOptr);
}