#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_27__ {size_t vnodeIdx; TYPE_20__* pState; int /*<<< orphan*/  pFinalColModel; int /*<<< orphan*/  pOrderDescriptor; int /*<<< orphan*/ * pExtMemBuffer; scalar_t__ numOfRetry; TYPE_4__* pParentSqlObj; int /*<<< orphan*/  queryMutex; TYPE_1__* localBuffer; } ;
struct TYPE_25__ {int code; scalar_t__ numOfRows; } ;
struct TYPE_24__ {int type; int /*<<< orphan*/  command; } ;
struct TYPE_26__ {TYPE_3__ res; int /*<<< orphan*/  param; int /*<<< orphan*/  (* fp ) (int /*<<< orphan*/ ,TYPE_4__*,int) ;TYPE_2__ cmd; int /*<<< orphan*/  rspSem; int /*<<< orphan*/  emptyRspSem; } ;
struct TYPE_23__ {int code; int /*<<< orphan*/  numOfTotal; int /*<<< orphan*/  numOfCompleted; } ;
struct TYPE_22__ {scalar_t__ numOfElems; } ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SRetrieveSupport ;

/* Variables and functions */
 scalar_t__ MAX_NUM_OF_SUBQUERY_RETRY ; 
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_SUCCESS ; 
 int TSDB_QUERY_TYPE_JOIN_SEC_STAGE ; 
 int /*<<< orphan*/  TSDB_SQL_RETRIEVE_METRIC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_fetch_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_val_compare_exchange_32 (int*,int,int) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  tExtMemBufferClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_20__*) ; 
 TYPE_4__* tscCreateSqlObjForSubquery (TYPE_4__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_4__*,TYPE_4__*,...) ; 
 void tscFreeSubSqlObj (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  tscLocalReducerEnvDestroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_4__*) ; 
 int /*<<< orphan*/  tscQueueAsyncRes (TYPE_4__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_4__*,TYPE_4__*,int,size_t,...) ; 
 int /*<<< orphan*/  tsem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tscHandleSubRetrievalError(SRetrieveSupport *trsupport, SSqlObj *pSql, int numOfRows) {
  SSqlObj *pPObj = trsupport->pParentSqlObj;
  int32_t  idx = trsupport->vnodeIdx;

  assert(pSql != NULL);

  /* retrieved in subquery failed. OR query cancelled in retrieve phase. */
  if (trsupport->pState->code == TSDB_CODE_SUCCESS && pPObj->res.code != TSDB_CODE_SUCCESS) {
    trsupport->pState->code = -(int)pPObj->res.code;

    /*
     * kill current sub-query connection, which may retrieve data from vnodes;
     * Here we get: pPObj->res.code == TSDB_CODE_QUERY_CANCELLED
     */
    pSql->res.numOfRows = 0;
    trsupport->numOfRetry = MAX_NUM_OF_SUBQUERY_RETRY;  // disable retry efforts
    tscTrace("%p query is cancelled, sub:%p, orderOfSub:%d abort retrieve, code:%d", trsupport->pParentSqlObj, pSql,
             trsupport->vnodeIdx, trsupport->pState->code);
  }

  if (numOfRows >= 0) {  // current query is successful, but other sub query failed, still abort current query.
    tscTrace("%p sub:%p retrieve numOfRows:%d,orderOfSub:%d", pPObj, pSql, numOfRows, idx);
    tscError("%p sub:%p abort further retrieval due to other queries failure,orderOfSub:%d,code:%d", pPObj, pSql, idx,
             trsupport->pState->code);
  } else {
    if (trsupport->numOfRetry++ < MAX_NUM_OF_SUBQUERY_RETRY && trsupport->pState->code == TSDB_CODE_SUCCESS) {
      /*
       * current query failed, and the retry count is less than the available
       * count, retry query clear previous retrieved data, then launch a new sub query
       */
      tExtMemBufferClear(trsupport->pExtMemBuffer[idx]);

      // clear local saved number of results
      trsupport->localBuffer->numOfElems = 0;
      pthread_mutex_unlock(&trsupport->queryMutex);

      tscTrace("%p sub:%p retrieve failed, code:%d, orderOfSub:%d, retry:%d", trsupport->pParentSqlObj, pSql, numOfRows,
               idx, trsupport->numOfRetry);

      SSqlObj *pNew = tscCreateSqlObjForSubquery(trsupport->pParentSqlObj, trsupport, pSql);
      if (pNew == NULL) {
        tscError("%p sub:%p failed to create new subquery sqlobj due to out of memory, abort retry",
                 trsupport->pParentSqlObj, pSql);

        trsupport->pState->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
        trsupport->numOfRetry = MAX_NUM_OF_SUBQUERY_RETRY;
        return;
      }

      tscProcessSql(pNew);
      return;
    } else {  // reach the maximum retry count, abort
      atomic_val_compare_exchange_32(&trsupport->pState->code, TSDB_CODE_SUCCESS, numOfRows);
      tscError("%p sub:%p retrieve failed,code:%d,orderOfSub:%d failed.no more retry,set global code:%d", pPObj, pSql,
               numOfRows, idx, trsupport->pState->code);
    }
  }

  if (atomic_add_fetch_32(&trsupport->pState->numOfCompleted, 1) < trsupport->pState->numOfTotal) {
    return tscFreeSubSqlObj(trsupport, pSql);
  }

  // all subqueries are failed
  tscError("%p retrieve from %d vnode(s) completed,code:%d.FAILED.", pPObj, trsupport->pState->numOfTotal,
           trsupport->pState->code);
  pPObj->res.code = -(trsupport->pState->code);

  // release allocated resource
  tscLocalReducerEnvDestroy(trsupport->pExtMemBuffer, trsupport->pOrderDescriptor, trsupport->pFinalColModel,
                            trsupport->pState->numOfTotal);

  tfree(trsupport->pState);
  tscFreeSubSqlObj(trsupport, pSql);

  // sync query, wait for the master SSqlObj to proceed
  if (pPObj->fp == NULL) {
    // sync query, wait for the master SSqlObj to proceed
    tsem_wait(&pPObj->emptyRspSem);
    tsem_wait(&pPObj->emptyRspSem);

    tsem_post(&pPObj->rspSem);

    pPObj->cmd.command = TSDB_SQL_RETRIEVE_METRIC;
  } else {
    // in case of second stage join subquery, invoke its callback function instead of regular QueueAsyncRes
    if ((pPObj->cmd.type & TSDB_QUERY_TYPE_JOIN_SEC_STAGE) == TSDB_QUERY_TYPE_JOIN_SEC_STAGE) {
      (*pPObj->fp)(pPObj->param, pPObj, pPObj->res.code);
    } else {  // regular super table query
      if (pPObj->res.code != TSDB_CODE_SUCCESS) {
        tscQueueAsyncRes(pPObj);
      }
    }
  }
}