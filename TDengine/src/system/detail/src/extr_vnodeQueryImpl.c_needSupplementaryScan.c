#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {size_t numOfOutputCols; TYPE_2__* pSelectExpr; } ;
struct TYPE_6__ {size_t functionId; } ;
struct TYPE_7__ {TYPE_1__ pBase; } ;
typedef  TYPE_3__ SQuery ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 size_t TSDB_FUNC_FIRST ; 
 size_t TSDB_FUNC_FIRST_DST ; 
 size_t TSDB_FUNC_LAST ; 
 size_t TSDB_FUNC_LAST_DST ; 
 size_t TSDB_FUNC_TAG ; 
 size_t TSDB_FUNC_TS ; 
 size_t TSDB_FUNC_TS_DUMMY ; 

bool needSupplementaryScan(SQuery *pQuery) {
  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    int32_t functionId = pQuery->pSelectExpr[i].pBase.functionId;
    if (functionId == TSDB_FUNC_TS || functionId == TSDB_FUNC_TS_DUMMY || functionId == TSDB_FUNC_TAG) {
      continue;
    }

    if (((functionId == TSDB_FUNC_LAST || functionId == TSDB_FUNC_LAST_DST) && QUERY_IS_ASC_QUERY(pQuery)) ||
        ((functionId == TSDB_FUNC_FIRST || functionId == TSDB_FUNC_FIRST_DST) && !QUERY_IS_ASC_QUERY(pQuery))) {
      return true;
    }
  }

  return false;
}