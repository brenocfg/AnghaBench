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
struct TYPE_5__ {scalar_t__ nSQLOptr; int /*<<< orphan*/  colInfo; struct TYPE_5__* pRight; struct TYPE_5__* pLeft; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TK_IN ; 
 scalar_t__ TK_LIKE ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  isTablenameToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ tablenameCondToString (TYPE_1__*,char*) ; 
 scalar_t__ tablenameListToString (TYPE_1__*,char*) ; 

__attribute__((used)) static int32_t getTablenameCond(SSqlCmd* pCmd, tSQLExpr* pTableCond, char* str) {
  const char* msg0 = "invalid table name list";

  if (pTableCond == NULL) {
    return TSDB_CODE_SUCCESS;
  }

  tSQLExpr* pLeft = pTableCond->pLeft;
  tSQLExpr* pRight = pTableCond->pRight;

  if (!isTablenameToken(&pLeft->colInfo)) {
    return TSDB_CODE_INVALID_SQL;
  }

  int32_t ret = TSDB_CODE_SUCCESS;

  if (pTableCond->nSQLOptr == TK_IN) {
    ret = tablenameListToString(pRight, str);
  } else if (pTableCond->nSQLOptr == TK_LIKE) {
    ret = tablenameCondToString(pRight, str);
  }

  if (ret != TSDB_CODE_SUCCESS) {
    setErrMsg(pCmd, msg0);
  }

  return ret;
}