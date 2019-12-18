#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int numOfGroupCols; int /*<<< orphan*/  orderByIdx; int /*<<< orphan*/  orderType; scalar_t__ groupbyTagIds; } ;
struct TYPE_5__ {int numOfGroupCols; int /*<<< orphan*/  columnInfo; int /*<<< orphan*/  orderIndex; int /*<<< orphan*/  orderType; } ;
typedef  TYPE_1__ SSqlGroupbyExpr ;
typedef  TYPE_2__ SQueryMeterMsg ;
typedef  int /*<<< orphan*/  SColIndexEx ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_SERV_OUT_OF_MEMORY ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

SSqlGroupbyExpr* vnodeCreateGroupbyExpr(SQueryMeterMsg* pQueryMsg, int32_t* code) {
  if (pQueryMsg->numOfGroupCols == 0) {
    return NULL;
  }

  // using group by tag columns
  SSqlGroupbyExpr* pGroupbyExpr =
      (SSqlGroupbyExpr*)malloc(sizeof(SSqlGroupbyExpr) + pQueryMsg->numOfGroupCols * sizeof(SColIndexEx));
  if (pGroupbyExpr == NULL) {
    *code = TSDB_CODE_SERV_OUT_OF_MEMORY;
    return NULL;
  }

  SColIndexEx* pGroupbyColInfo = (SColIndexEx*)pQueryMsg->groupbyTagIds;

  pGroupbyExpr->numOfGroupCols = pQueryMsg->numOfGroupCols;
  pGroupbyExpr->orderType = pQueryMsg->orderType;
  pGroupbyExpr->orderIndex = pQueryMsg->orderByIdx;

  memcpy(pGroupbyExpr->columnInfo, pGroupbyColInfo, sizeof(SColIndexEx) * pGroupbyExpr->numOfGroupCols);

  // TODO: update the colIndexInBuf for each column in group by clause

  return pGroupbyExpr;
}