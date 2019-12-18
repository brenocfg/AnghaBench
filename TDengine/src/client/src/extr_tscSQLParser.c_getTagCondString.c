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
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  isExprDirectParentOfLeaftNode (TYPE_1__*) ; 
 int /*<<< orphan*/  relToString (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 scalar_t__ tSQLExprLeafToString (TYPE_1__*,int,char**) ; 

__attribute__((used)) static int32_t getTagCondString(SSqlCmd* pCmd, tSQLExpr* pExpr, char** str) {
  if (pExpr == NULL) {
    return TSDB_CODE_SUCCESS;
  }

  if (!isExprDirectParentOfLeaftNode(pExpr)) {
    *(*str) = '(';
    *str += 1;

    int32_t ret = getTagCondString(pCmd, pExpr->pLeft, str);
    if (ret != TSDB_CODE_SUCCESS) {
      return ret;
    }

    relToString(pCmd, pExpr, str);

    ret = getTagCondString(pCmd, pExpr->pRight, str);

    *(*str) = ')';
    *str += 1;

    return ret;
  }

  return tSQLExprLeafToString(pExpr, true, str);
}