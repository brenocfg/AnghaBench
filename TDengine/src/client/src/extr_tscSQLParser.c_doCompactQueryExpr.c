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
struct TYPE_5__ {scalar_t__ nSQLOptr; struct TYPE_5__* pLeft; struct TYPE_5__* pRight; } ;
typedef  TYPE_1__ tSQLExpr ;

/* Variables and functions */
 scalar_t__ TK_AND ; 
 scalar_t__ TK_OR ; 
 scalar_t__ isExprDirectParentOfLeaftNode (TYPE_1__*) ; 
 int /*<<< orphan*/  tSQLExprNodeDestroy (TYPE_1__*) ; 

__attribute__((used)) static void doCompactQueryExpr(tSQLExpr** pExpr) {
  if (*pExpr == NULL || isExprDirectParentOfLeaftNode(*pExpr)) {
    return;
  }

  if ((*pExpr)->pLeft) {
    doCompactQueryExpr(&(*pExpr)->pLeft);
  }

  if ((*pExpr)->pRight) {
    doCompactQueryExpr(&(*pExpr)->pRight);
  }

  if ((*pExpr)->pLeft == NULL && (*pExpr)->pRight == NULL &&
      ((*pExpr)->nSQLOptr == TK_OR || (*pExpr)->nSQLOptr == TK_AND)) {
    tSQLExprNodeDestroy(*pExpr);
    *pExpr = NULL;

  } else if ((*pExpr)->pLeft == NULL && (*pExpr)->pRight != NULL) {
    tSQLExpr* tmpPtr = (*pExpr)->pRight;
    tSQLExprNodeDestroy(*pExpr);

    (*pExpr) = tmpPtr;
  } else if ((*pExpr)->pRight == NULL && (*pExpr)->pLeft != NULL) {
    tSQLExpr* tmpPtr = (*pExpr)->pLeft;
    tSQLExprNodeDestroy(*pExpr);

    (*pExpr) = tmpPtr;
  }
}