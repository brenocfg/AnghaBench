#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pState; } ;
struct TYPE_12__ {int numOfExprs; } ;
struct TYPE_16__ {TYPE_1__ exprsInfo; } ;
struct TYPE_14__ {scalar_t__ numOfRows; void** tsrow; scalar_t__ row; scalar_t__ code; TYPE_2__* pColumnIndex; } ;
struct TYPE_15__ {size_t numOfSubs; TYPE_3__ res; struct TYPE_15__** pSubs; scalar_t__ param; TYPE_5__ cmd; } ;
struct TYPE_13__ {size_t tableIndex; size_t columnIndex; } ;
typedef  scalar_t__ TSKEY ;
typedef  int /*<<< orphan*/  SSubqueryState ;
typedef  TYPE_3__ SSqlRes ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SJoinSubquerySupporter ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  doSetResultRowData (TYPE_4__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void** malloc (int) ; 
 int /*<<< orphan*/  taos_free_result (TYPE_4__*) ; 
 int /*<<< orphan*/  tscDestroyJoinSupporter (scalar_t__) ; 
 int /*<<< orphan*/  tscFetchDatablockFromSubquery (TYPE_4__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_4__*,int) ; 

__attribute__((used)) static void **tscJoinResultsetFromBuf(SSqlObj *pSql) {
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  while (1) {
    bool hasData = true;

    for (int32_t i = 0; i < pSql->numOfSubs; ++i) {
      SSqlRes *pRes1 = &pSql->pSubs[i]->res;

      // in case inner join, if any subquery exhausted, query completed
      if (pRes1->numOfRows == 0) {
        hasData = false;
        break;
      }
    }

    if (!hasData) {  // free all sub sqlobj
      tscTrace("%p one subquery exhausted, free other %d subquery", pSql, pSql->numOfSubs - 1);

      SSubqueryState *pState = NULL;

      for (int32_t i = 0; i < pSql->numOfSubs; ++i) {
        SSqlObj *               pChildObj = pSql->pSubs[i];
        SJoinSubquerySupporter *pSupporter = (SJoinSubquerySupporter *)pChildObj->param;
        pState = pSupporter->pState;

        tscDestroyJoinSupporter(pChildObj->param);
        taos_free_result(pChildObj);
      }

      free(pState);
      return NULL;
    }

    if (pRes->tsrow == NULL) {
      pRes->tsrow = malloc(sizeof(void *) * pCmd->exprsInfo.numOfExprs);
    }

    bool success = false;
    if (pSql->numOfSubs >= 2) {
      // do merge result
      SSqlRes *pRes1 = &pSql->pSubs[0]->res;
      SSqlRes *pRes2 = &pSql->pSubs[1]->res;

      while (pRes1->row < pRes1->numOfRows && pRes2->row < pRes2->numOfRows) {
        doSetResultRowData(pSql->pSubs[0]);
        doSetResultRowData(pSql->pSubs[1]);

        TSKEY key1 = *(TSKEY *)pRes1->tsrow[0];
        TSKEY key2 = *(TSKEY *)pRes2->tsrow[0];

        if (key1 == key2) {
          success = true;
          pRes1->row++;
          pRes2->row++;
          break;
        } else if (key1 < key2) {
          pRes1->row++;
        } else if (key1 > key2) {
          pRes2->row++;
        }
      }
    } else {
      SSqlRes *pRes1 = &pSql->pSubs[0]->res;
      doSetResultRowData(pSql->pSubs[0]);

      success = (pRes1->row++ < pRes1->numOfRows);
    }

    if (success) {
      for (int32_t i = 0; i < pCmd->exprsInfo.numOfExprs; ++i) {
        int32_t tableIndex = pRes->pColumnIndex[i].tableIndex;
        int32_t columnIndex = pRes->pColumnIndex[i].columnIndex;

        SSqlRes *pRes1 = &pSql->pSubs[tableIndex]->res;
        pRes->tsrow[i] = pRes1->tsrow[columnIndex];
      }

      break;
    } else {
      tscFetchDatablockFromSubquery(pSql);
      if (pRes->code != TSDB_CODE_SUCCESS) {
        return NULL;
      }
    }
  }

  return pRes->tsrow;
}