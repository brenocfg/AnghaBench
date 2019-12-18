#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tSQLExpr ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TK_OR ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * tSQLExprCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int32_t setExprToCond(SSqlCmd* pCmd, tSQLExpr** parent, tSQLExpr* pExpr, const char* msg, int32_t parentOptr) {
  if (*parent != NULL) {
    if (parentOptr == TK_OR && msg != NULL) {
      setErrMsg(pCmd, msg);
      return TSDB_CODE_INVALID_SQL;
    }

    *parent = tSQLExprCreate((*parent), pExpr, parentOptr);
  } else {
    *parent = pExpr;
  }

  return TSDB_CODE_SUCCESS;
}