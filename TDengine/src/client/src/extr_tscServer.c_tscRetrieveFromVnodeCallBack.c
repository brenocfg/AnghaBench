#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_38__ ;
typedef  struct TYPE_43__   TYPE_31__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_22__ ;
typedef  struct TYPE_40__   TYPE_20__ ;
typedef  struct TYPE_39__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_42__ {TYPE_31__* pSchema; } ;
typedef  TYPE_2__ tOrderDescriptor ;
typedef  size_t int32_t ;
struct TYPE_51__ {int /*<<< orphan*/  pMetricMeta; } ;
struct TYPE_50__ {size_t vnodeIdx; TYPE_38__* pState; int /*<<< orphan*/  pFinalColModel; TYPE_20__** pExtMemBuffer; TYPE_22__* localBuffer; int /*<<< orphan*/  queryMutex; TYPE_2__* pOrderDescriptor; TYPE_6__* pParentSqlObj; } ;
struct TYPE_39__ {int /*<<< orphan*/  orderType; } ;
struct TYPE_49__ {size_t vnodeIdx; int /*<<< orphan*/  command; TYPE_1__ groupbyExpr; } ;
struct TYPE_47__ {scalar_t__ code; int numOfRows; scalar_t__ row; int /*<<< orphan*/  precision; int /*<<< orphan*/  data; } ;
struct TYPE_48__ {int /*<<< orphan*/  param; int /*<<< orphan*/  (* fp ) (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ;TYPE_5__ res; TYPE_7__ cmd; int /*<<< orphan*/  rspSem; int /*<<< orphan*/  emptyRspSem; } ;
struct TYPE_46__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  ip; } ;
struct TYPE_45__ {size_t index; TYPE_4__* vpeerDesc; } ;
struct TYPE_44__ {scalar_t__ code; int /*<<< orphan*/  numOfTotal; int /*<<< orphan*/  numOfCompleted; int /*<<< orphan*/  numOfRetrievedRows; } ;
struct TYPE_43__ {int /*<<< orphan*/  maxCapacity; } ;
struct TYPE_41__ {int numOfElems; int /*<<< orphan*/  data; } ;
struct TYPE_40__ {int /*<<< orphan*/  numOfElemsPerPage; scalar_t__ numOfAllElems; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_3__ SVnodeSidList ;
typedef  TYPE_4__ SVPeerDesc ;
typedef  int /*<<< orphan*/  SSrcColumnInfo ;
typedef  TYPE_5__ SSqlRes ;
typedef  TYPE_6__ SSqlObj ;
typedef  TYPE_7__ SSqlCmd ;
typedef  TYPE_8__ SRetrieveSupport ;
typedef  TYPE_9__ SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_CLI_NO_DISKSPACE ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_SQL_RETRIEVE_METRIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_add_fetch_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_add_fetch_64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_38__*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t saveToBuffer (TYPE_20__*,TYPE_2__*,TYPE_22__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tColModelCompact (TYPE_31__*,TYPE_22__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tColModelDisplayEx (TYPE_31__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_fetch_rows_a (int /*<<< orphan*/ *,void (*) (void*,int /*<<< orphan*/ *,int),void*) ; 
 scalar_t__ tsAvailTmpDirGB ; 
 scalar_t__ tsMinimalTmpDirGB ; 
 scalar_t__ tsTotalTmpDirGB ; 
 void tscAbortFurtherRetryRetrieval (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscClearInterpInfo (TYPE_7__*) ; 
 int /*<<< orphan*/  tscCreateLocalReducer (TYPE_20__**,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_6__*,TYPE_6__*,scalar_t__,scalar_t__) ; 
 size_t tscFlushTmpBuffer (TYPE_20__*,TYPE_2__*,TYPE_22__*,int /*<<< orphan*/ ) ; 
 void tscFreeSubSqlObj (TYPE_8__*,TYPE_6__*) ; 
 TYPE_9__* tscGetMeterMetaInfo (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscGetSrcColumnInfo (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_3__* tscGetVnodeSidList (int /*<<< orphan*/ ,size_t) ; 
 void tscHandleSubRetrievalError (TYPE_8__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  tscQueueAsyncRes (TYPE_6__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_6__*,...) ; 
 int /*<<< orphan*/  tsem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsem_wait (int /*<<< orphan*/ *) ; 

void tscRetrieveFromVnodeCallBack(void *param, TAOS_RES *tres, int numOfRows) {
  SRetrieveSupport *trsupport = (SRetrieveSupport *)param;
  int32_t           idx = trsupport->vnodeIdx;
  SSqlObj *         pPObj = trsupport->pParentSqlObj;
  tOrderDescriptor *pDesc = trsupport->pOrderDescriptor;

  SSqlObj *pSql = (SSqlObj *)tres;
  if (pSql == NULL) {
    /* sql object has been released in error process, return immediately */
    tscTrace("%p subquery has been released, idx:%d, abort", pPObj, idx);
    return;
  }

  // query process and cancel query process may execute at the same time
  pthread_mutex_lock(&trsupport->queryMutex);

  if (numOfRows < 0 || trsupport->pState->code < 0 || pPObj->res.code != TSDB_CODE_SUCCESS) {
    return tscHandleSubRetrievalError(trsupport, pSql, numOfRows);
  }

  SSqlRes *       pRes = &pSql->res;
  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  SVnodeSidList *vnodeInfo = tscGetVnodeSidList(pMeterMetaInfo->pMetricMeta, idx);
  SVPeerDesc *   pSvd = &vnodeInfo->vpeerDesc[vnodeInfo->index];

  if (numOfRows > 0) {
    assert(pRes->numOfRows == numOfRows);
    atomic_add_fetch_64(&trsupport->pState->numOfRetrievedRows, numOfRows);

    tscTrace("%p sub:%p retrieve numOfRows:%d totalNumOfRows:%d from ip:%u,vid:%d,orderOfSub:%d", pPObj, pSql,
             pRes->numOfRows, trsupport->pState->numOfRetrievedRows, pSvd->ip, pSvd->vnode, idx);

#ifdef _DEBUG_VIEW
    printf("received data from vnode: %d rows\n", pRes->numOfRows);
    SSrcColumnInfo colInfo[256] = {0};
    tscGetSrcColumnInfo(colInfo, &pPObj->cmd);
    tColModelDisplayEx(pDesc->pSchema, pRes->data, pRes->numOfRows, pRes->numOfRows, colInfo);
#endif
    if (tsTotalTmpDirGB != 0 && tsAvailTmpDirGB < tsMinimalTmpDirGB) {
      tscError("%p sub:%p client disk space remain %.3f GB, need at least %.3f GB, stop query", pPObj, pSql,
               tsAvailTmpDirGB, tsMinimalTmpDirGB);
      tscAbortFurtherRetryRetrieval(trsupport, tres, TSDB_CODE_CLI_NO_DISKSPACE);
      return;
    }
    int32_t ret = saveToBuffer(trsupport->pExtMemBuffer[idx], pDesc, trsupport->localBuffer, pRes->data,
                               pRes->numOfRows, pCmd->groupbyExpr.orderType);
    if (ret < 0) {
      // set no disk space error info, and abort retry
      tscAbortFurtherRetryRetrieval(trsupport, tres, TSDB_CODE_CLI_NO_DISKSPACE);
    } else {
      pthread_mutex_unlock(&trsupport->queryMutex);
      taos_fetch_rows_a(tres, tscRetrieveFromVnodeCallBack, param);
    }

  } else {  // all data has been retrieved to client
    /* data in from current vnode is stored in cache and disk */
    uint32_t numOfRowsFromVnode =
        trsupport->pExtMemBuffer[pCmd->vnodeIdx]->numOfAllElems + trsupport->localBuffer->numOfElems;
    tscTrace("%p sub:%p all data retrieved from ip:%u,vid:%d, numOfRows:%d, orderOfSub:%d", pPObj, pSql, pSvd->ip,
             pSvd->vnode, numOfRowsFromVnode, idx);

    tColModelCompact(pDesc->pSchema, trsupport->localBuffer, pDesc->pSchema->maxCapacity);

#ifdef _DEBUG_VIEW
    printf("%ld rows data flushed to disk:\n", trsupport->localBuffer->numOfElems);
    SSrcColumnInfo colInfo[256] = {0};
    tscGetSrcColumnInfo(colInfo, &pPObj->cmd);
    tColModelDisplayEx(pDesc->pSchema, trsupport->localBuffer->data, trsupport->localBuffer->numOfElems,
                       trsupport->localBuffer->numOfElems, colInfo);
#endif
    if (tsTotalTmpDirGB != 0 && tsAvailTmpDirGB < tsMinimalTmpDirGB) {
      tscError("%p sub:%p client disk space remain %.3f GB, need at least %.3f GB, stop query", pPObj, pSql,
               tsAvailTmpDirGB, tsMinimalTmpDirGB);
      tscAbortFurtherRetryRetrieval(trsupport, tres, TSDB_CODE_CLI_NO_DISKSPACE);
      return;
    }

    // each result for a vnode is ordered as an independant list,
    // then used as an input of loser tree for disk-based merge routine
    int32_t ret =
        tscFlushTmpBuffer(trsupport->pExtMemBuffer[idx], pDesc, trsupport->localBuffer, pCmd->groupbyExpr.orderType);
    if (ret != 0) {
      /* set no disk space error info, and abort retry */
      return tscAbortFurtherRetryRetrieval(trsupport, tres, TSDB_CODE_CLI_NO_DISKSPACE);
    }

    if (atomic_add_fetch_32(&trsupport->pState->numOfCompleted, 1) < trsupport->pState->numOfTotal) {
      return tscFreeSubSqlObj(trsupport, pSql);
    }

    // all sub-queries are returned, start to local merge process
    pDesc->pSchema->maxCapacity = trsupport->pExtMemBuffer[idx]->numOfElemsPerPage;

    tscTrace("%p retrieve from %d vnodes completed.final NumOfRows:%d,start to build loser tree", pPObj,
             trsupport->pState->numOfTotal, trsupport->pState->numOfCompleted);

    tscClearInterpInfo(&pPObj->cmd);
    tscCreateLocalReducer(trsupport->pExtMemBuffer, trsupport->pState->numOfTotal, pDesc, trsupport->pFinalColModel,
                          &pPObj->cmd, &pPObj->res);
    tscTrace("%p build loser tree completed", pPObj);

    pPObj->res.precision = pSql->res.precision;
    pPObj->res.numOfRows = 0;
    pPObj->res.row = 0;

    // only free once
    free(trsupport->pState);
    tscFreeSubSqlObj(trsupport, pSql);

    if (pPObj->fp == NULL) {
      tsem_wait(&pPObj->emptyRspSem);
      tsem_wait(&pPObj->emptyRspSem);

      tsem_post(&pPObj->rspSem);
    } else {
      // set the command flag must be after the semaphore been correctly set.
      pPObj->cmd.command = TSDB_SQL_RETRIEVE_METRIC;
      if (pPObj->res.code == TSDB_CODE_SUCCESS) {
        (*pPObj->fp)(pPObj->param, pPObj, 0);
      } else {
        tscQueueAsyncRes(pPObj);
      }
    }
  }
}