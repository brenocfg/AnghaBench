#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ limit; int /*<<< orphan*/  offset; } ;
struct TYPE_17__ {scalar_t__ vnodeIdx; scalar_t__ globalLimit; scalar_t__ command; TYPE_1__ limit; } ;
struct TYPE_15__ {scalar_t__ numOfTotal; scalar_t__ numOfRows; int /*<<< orphan*/  offset; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* fetchFp ) (void*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  fp; TYPE_5__ cmd; TYPE_3__ res; } ;
struct TYPE_14__ {scalar_t__ numOfVnodes; } ;
struct TYPE_12__ {TYPE_2__* pMetricMeta; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_3__ SSqlRes ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_SQL_RETRIEVE_METRIC ; 
 scalar_t__ TSDB_SQL_SELECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ *,int) ; 
 TYPE_10__* tscGetMeterMetaInfo (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscProcessAsyncRetrieveNextVnode ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_4__*) ; 
 scalar_t__ tscProjectionQueryOnMetric (TYPE_5__*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_3__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static void tscProcessAsyncFetchRowsProxy(void *param, TAOS_RES *tres, int numOfRows) {
  if (tres == NULL) {
    return;
  }

  SSqlObj *pSql = (SSqlObj *)tres;
  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;

  // sequentially retrieve data from remain vnodes first, query vnode specified by vnodeIdx
  if (numOfRows == 0 && tscProjectionQueryOnMetric(pCmd)) {
    // vnode is denoted by vnodeIdx, continue to query vnode specified by vnodeIdx
    assert(pCmd->vnodeIdx >= 0);

    /* reach the maximum number of output rows, abort */
    if (pCmd->globalLimit > 0 && pRes->numOfTotal >= pCmd->globalLimit) {
      (*pSql->fetchFp)(param, tres, 0);
      return;
    }

    /* update the limit value according to current retrieval results */
    pCmd->limit.limit = pCmd->globalLimit - pRes->numOfTotal;
    pCmd->limit.offset = pRes->offset;

    if ((++(pCmd->vnodeIdx)) < tscGetMeterMetaInfo(pCmd, 0)->pMetricMeta->numOfVnodes) {
      tscTrace("%p retrieve data from next vnode:%d", pSql, pCmd->vnodeIdx);

      pSql->cmd.command = TSDB_SQL_SELECT;  // reset flag to launch query first.

      tscResetForNextRetrieve(pRes);
      pSql->fp = tscProcessAsyncRetrieveNextVnode;
      tscProcessSql(pSql);
      return;
    }
  } else { // localreducer has handle this situation
    if (pCmd->command != TSDB_SQL_RETRIEVE_METRIC) {
      pRes->numOfTotal += pRes->numOfRows;
    }
  }

  (*pSql->fetchFp)(param, tres, numOfRows);
}