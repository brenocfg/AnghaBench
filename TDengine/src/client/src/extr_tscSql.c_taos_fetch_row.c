#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* pMetricMeta; } ;
struct TYPE_11__ {scalar_t__ limit; scalar_t__ offset; } ;
struct TYPE_15__ {scalar_t__ globalLimit; scalar_t__ vnodeIdx; int /*<<< orphan*/  command; TYPE_1__ limit; } ;
struct TYPE_13__ {scalar_t__ numOfTotal; scalar_t__ offset; scalar_t__ numOfRows; } ;
struct TYPE_14__ {int /*<<< orphan*/ * fp; struct TYPE_14__* signature; TYPE_3__ res; TYPE_5__ cmd; } ;
struct TYPE_12__ {scalar_t__ numOfVnodes; } ;
typedef  int /*<<< orphan*/ * TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_3__ SSqlRes ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_DISCONNECTED ; 
 int /*<<< orphan*/  TSDB_SQL_SELECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  globalCode ; 
 int /*<<< orphan*/ * taos_fetch_row_impl (int /*<<< orphan*/ *) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_4__*) ; 
 scalar_t__ tscProjectionQueryOnMetric (TYPE_5__*) ; 

TAOS_ROW taos_fetch_row(TAOS_RES *res) {
  SSqlObj *pSql = (SSqlObj *)res;
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  if (pSql == NULL || pSql->signature != pSql) {
    globalCode = TSDB_CODE_DISCONNECTED;
    return NULL;
  }

  // projection query on metric, pipeline retrieve data from vnode list, instead of two-stage merge
  TAOS_ROW rows = taos_fetch_row_impl(res);
  while (rows == NULL && tscProjectionQueryOnMetric(pCmd)) {
    SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

    // reach the maximum number of output rows, abort
    if (pCmd->globalLimit > 0 && pRes->numOfTotal >= pCmd->globalLimit) {
      return NULL;
    }

    /*
     * update the limit and offset value according to current retrieval results
     * Note: if pRes->offset > 0, pRes->numOfRows = 0, pRes->numOfTotal = 0;
     */
    pCmd->limit.limit = pCmd->globalLimit - pRes->numOfTotal;
    pCmd->limit.offset = pRes->offset;

    assert((pRes->offset >= 0 && pRes->numOfRows == 0) || (pRes->offset == 0 && pRes->numOfRows >= 0));

    if ((++pCmd->vnodeIdx) < pMeterMetaInfo->pMetricMeta->numOfVnodes) {
      pCmd->command = TSDB_SQL_SELECT;
      assert(pSql->fp == NULL);
      tscProcessSql(pSql);
      rows = taos_fetch_row_impl(res);
    }

    // check!!!
    if (rows != NULL || pCmd->vnodeIdx >= pMeterMetaInfo->pMetricMeta->numOfVnodes) {
      break;
    }
  }

  return rows;
}