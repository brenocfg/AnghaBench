#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tOrderDescriptor ;
typedef  int /*<<< orphan*/  tFilePage ;
typedef  int /*<<< orphan*/  tExtMemBuffer ;
typedef  int /*<<< orphan*/  tColModel ;
struct TYPE_28__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ pthread_mutexattr_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_33__ {TYPE_1__* pMetricMeta; } ;
struct TYPE_32__ {int /*<<< orphan*/  queryMutex; int /*<<< orphan*/ * pFinalColModel; TYPE_5__* pParentSqlObj; scalar_t__ vnodeIdx; int /*<<< orphan*/ * localBuffer; TYPE_3__* pState; int /*<<< orphan*/ * pOrderDescriptor; int /*<<< orphan*/ ** pExtMemBuffer; } ;
struct TYPE_26__ {int /*<<< orphan*/  vnodeIdx; scalar_t__ tsBuf; int /*<<< orphan*/  command; } ;
struct TYPE_30__ {scalar_t__ code; int qhandle; } ;
struct TYPE_31__ {TYPE_15__ cmd; TYPE_4__ res; scalar_t__ numOfSubs; int /*<<< orphan*/  pSubs; scalar_t__ fp; } ;
struct TYPE_29__ {int /*<<< orphan*/  numOfCompleted; scalar_t__ numOfTotal; } ;
struct TYPE_27__ {scalar_t__ numOfVnodes; } ;
typedef  TYPE_3__ SSubqueryState ;
typedef  TYPE_4__ SSqlRes ;
typedef  TYPE_5__ SSqlObj ;
typedef  TYPE_6__ SRetrieveSupport ;
typedef  TYPE_7__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ POINTER_BYTES ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE_NP ; 
 scalar_t__ TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 scalar_t__ TSDB_CODE_QUERY_CANCELLED ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_SQL_RETRIEVE_METRIC ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* calloc (int,int const) ; 
 int /*<<< orphan*/  doCleanupSubqueries (TYPE_5__*,scalar_t__,scalar_t__,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_3__*) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tsBufClone (scalar_t__) ; 
 TYPE_5__* tscCreateSqlObjForSubquery (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_15__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tscLocalReducerEnvCreate (TYPE_5__*,int /*<<< orphan*/ ***,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int const) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_5__*) ; 
 int /*<<< orphan*/  tscQueueAsyncRes (TYPE_5__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_5__*,TYPE_5__*,...) ; 

int tscLaunchMetricSubQueries(SSqlObj *pSql) {
  SSqlRes *pRes = &pSql->res;

  // pRes->code check only serves in launching metric sub-queries
  if (pRes->code == TSDB_CODE_QUERY_CANCELLED) {
    pSql->cmd.command = TSDB_SQL_RETRIEVE_METRIC;  // enable the abort of kill metric function.
    return pSql->res.code;
  }

  tExtMemBuffer **  pMemoryBuf = NULL;
  tOrderDescriptor *pDesc = NULL;
  tColModel *       pModel = NULL;

  pRes->qhandle = 1;  // hack the qhandle check

  const uint32_t  nBufferSize = (1 << 16);  // 64KB
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(&pSql->cmd, 0);
  int32_t         numOfVnodes = pMeterMetaInfo->pMetricMeta->numOfVnodes;
  assert(numOfVnodes > 0);

  int32_t ret = tscLocalReducerEnvCreate(pSql, &pMemoryBuf, &pDesc, &pModel, nBufferSize);
  if (ret != 0) {
    pRes->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
    if (pSql->fp) {
      tscQueueAsyncRes(pSql);
    }
    return pRes->code;
  }

  pSql->pSubs = malloc(POINTER_BYTES * numOfVnodes);
  pSql->numOfSubs = numOfVnodes;

  tscTrace("%p retrieved query data from %d vnode(s)", pSql, numOfVnodes);
  SSubqueryState *pState = calloc(1, sizeof(SSubqueryState));
  pState->numOfTotal = numOfVnodes;
  pRes->code = TSDB_CODE_SUCCESS;

  for (int32_t i = 0; i < numOfVnodes; ++i) {
    if (pRes->code == TSDB_CODE_QUERY_CANCELLED || pRes->code == TSDB_CODE_CLI_OUT_OF_MEMORY) {
      /*
       * during launch sub queries, if the master query is cancelled. the remain is ignored and set the retrieveDoneRec
       * to the value of remaining not built sub-queries. So, the already issued sub queries can successfully free
       * allocated resources.
       */
      pState->numOfCompleted = (numOfVnodes - i);
      doCleanupSubqueries(pSql, i, numOfVnodes, NULL, pDesc, pModel, pMemoryBuf, pState);

      if (i == 0) {
        return pSql->res.code;
      }

      break;
    }

    SRetrieveSupport *trs = (SRetrieveSupport *)calloc(1, sizeof(SRetrieveSupport));
    trs->pExtMemBuffer = pMemoryBuf;
    trs->pOrderDescriptor = pDesc;
    trs->pState = pState;
    trs->localBuffer = (tFilePage *)calloc(1, nBufferSize + sizeof(tFilePage));
    trs->vnodeIdx = i;
    trs->pParentSqlObj = pSql;
    trs->pFinalColModel = pModel;

    pthread_mutexattr_t mutexattr = {0};
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&trs->queryMutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);

    SSqlObj *pNew = tscCreateSqlObjForSubquery(pSql, trs, NULL);

    if (pNew == NULL) {
      pState->numOfCompleted = (numOfVnodes - i);
      doCleanupSubqueries(pSql, i, numOfVnodes, trs, pDesc, pModel, pMemoryBuf, pState);

      if (i == 0) {
        return pSql->res.code;
      }

      break;
    }

    // todo handle multi-vnode situation
    if (pSql->cmd.tsBuf) {
      pNew->cmd.tsBuf = tsBufClone(pSql->cmd.tsBuf);
    }

    tscTrace("%p sub:%p launch subquery.orderOfSub:%d", pSql, pNew, pNew->cmd.vnodeIdx);
    tscProcessSql(pNew);
  }

  return TSDB_CODE_SUCCESS;
}