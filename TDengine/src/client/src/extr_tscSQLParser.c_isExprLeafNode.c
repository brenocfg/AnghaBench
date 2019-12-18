#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nSQLOptr; int /*<<< orphan*/ * pLeft; int /*<<< orphan*/ * pRight; } ;
typedef  TYPE_1__ tSQLExpr ;

/* Variables and functions */
 scalar_t__ TK_BOOL ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TK_NCHAR ; 
 scalar_t__ TK_SET ; 

__attribute__((used)) static bool isExprLeafNode(tSQLExpr* pExpr) {
  return (pExpr->pRight == NULL && pExpr->pLeft == NULL) &&
         (pExpr->nSQLOptr == TK_ID || (pExpr->nSQLOptr >= TK_BOOL && pExpr->nSQLOptr <= TK_NCHAR) ||
          pExpr->nSQLOptr == TK_SET);
}