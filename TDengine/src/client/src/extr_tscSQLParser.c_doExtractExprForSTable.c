#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* pRight; struct TYPE_11__* pLeft; int /*<<< orphan*/  nSQLOptr; int /*<<< orphan*/  colInfo; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;
struct TYPE_13__ {scalar_t__ tableIndex; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SSQLToken ;
typedef  TYPE_3__ SColumnIndex ;

/* Variables and functions */
 TYPE_3__ COLUMN_INDEX_INITIALIZER ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  extractTableNameFromToken (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ getColumnIndexByNameEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ isExprDirectParentOfLeaftNode (TYPE_1__*) ; 
 TYPE_1__* tSQLExprCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doExtractExprForSTable(tSQLExpr** pExpr, SSqlCmd* pCmd, tSQLExpr** pOut, int32_t tableIndex) {
  if (isExprDirectParentOfLeaftNode(*pExpr)) {
    tSQLExpr* pLeft = (*pExpr)->pLeft;

    SColumnIndex index = COLUMN_INDEX_INITIALIZER;
    if (getColumnIndexByNameEx(&pLeft->colInfo, pCmd, &index) != TSDB_CODE_SUCCESS) {
      return;
    }

    if (index.tableIndex != tableIndex) {
      return;
    }

    SSQLToken t = {0};
    extractTableNameFromToken(&pLeft->colInfo, &t);

    *pOut = *pExpr;
    (*pExpr) = NULL;

  } else {
    *pOut = tSQLExprCreate(NULL, NULL, (*pExpr)->nSQLOptr);

    doExtractExprForSTable(&(*pExpr)->pLeft, pCmd, &((*pOut)->pLeft), tableIndex);
    doExtractExprForSTable(&(*pExpr)->pRight, pCmd, &((*pOut)->pRight), tableIndex);
  }
}