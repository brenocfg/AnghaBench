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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  doCompactQueryExpr (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  doExtractExprForSTable (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tSQLExpr* extractExprForSTable(tSQLExpr** pExpr, SSqlCmd* pCmd, int32_t tableIndex) {
  tSQLExpr* pResExpr = NULL;

  if (*pExpr != NULL) {
    doExtractExprForSTable(pExpr, pCmd, &pResExpr, tableIndex);
    doCompactQueryExpr(&pResExpr);
  }

  return pResExpr;
}