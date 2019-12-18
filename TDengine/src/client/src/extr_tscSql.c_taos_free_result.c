#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * pMeterMeta; } ;
struct TYPE_13__ {scalar_t__ command; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {scalar_t__ qhandle; scalar_t__ code; scalar_t__ numOfRows; } ;
struct TYPE_12__ {int freed; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * thandle; int /*<<< orphan*/ * pStream; struct TYPE_12__* signature; TYPE_3__ cmd; TYPE_1__ res; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_QUERY_CANCELLED ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_QUERY_TYPE_FREE_RESOURCE ; 
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 scalar_t__ TSDB_SQL_SELECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tscFreeSqlObj (TYPE_2__*) ; 
 int /*<<< orphan*/  tscFreeSqlObjPartial (TYPE_2__*) ; 
 TYPE_4__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_2__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*,...) ; 

void taos_free_result(TAOS_RES *res) {
  if (res == NULL) return;

  SSqlObj *pSql = (SSqlObj *)res;
  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;

  tscTrace("%p start to free result", pSql);

  if (pSql->signature != pSql) return;

  if (pRes == NULL || pRes->qhandle == 0) {
    /* Query rsp is not received from vnode, so the qhandle is NULL */
    tscTrace("%p qhandle is null, abort free, fp:%p", pSql, pSql->fp);
    if (pSql->fp != NULL) {
      pSql->thandle = NULL;
      tscFreeSqlObj(pSql);
      tscTrace("%p Async SqlObj is freed by app", pSql);
    } else {
      tscFreeSqlObjPartial(pSql);
    }
    return;
  }

  // set freeFlag to 1 in retrieve message if there are un-retrieved results
  pCmd->type = TSDB_QUERY_TYPE_FREE_RESOURCE;

  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  /*
   * case 1. Partial data have been retrieved from vnodes, but not all data has been retrieved yet.
   *         We need to recycle the connection by noticing the vnode return 0 results.
   * case 2. When the query response is received from vnodes and the numOfRows is set to 0, the user calls
   *         taos_free_result before the taos_fetch_row is called in non-stream computing,
   *         we need to recycle the connection.
   * case 3. If the query process is cancelled by user in stable query, tscProcessSql should not be called
   *         for each subquery. Because the failure of execution tsProcessSql may trigger the callback function
   *         be executed, and the retry efforts may result in double free the resources, e.g.,SRetrieveSupport
   */
  if (pRes->code != TSDB_CODE_QUERY_CANCELLED &&
      ((pRes->numOfRows > 0 && pCmd->command < TSDB_SQL_LOCAL) ||
       (pRes->code == TSDB_CODE_SUCCESS && pRes->numOfRows == 0 && pCmd->command == TSDB_SQL_SELECT &&
        pSql->pStream == NULL && pMeterMetaInfo->pMeterMeta != NULL))) {
    pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;

    void *fp = pSql->fp;
    if (fp != NULL) {
      pSql->freed = 1;
    }

    tscProcessSql(pSql);

    /*
     *  If release connection msg is sent to vnode, the corresponding SqlObj for async query can not be freed instantly,
     *  since its free operation is delegated to callback function, which is tscProcessMsgFromServer.
     */
    if (fp == NULL) {
      /*
       * fp may be released here, so we cannot use the pSql->fp
       *
       * In case of handle sync model query, the main SqlObj cannot be freed.
       * So, we only free part attributes, including allocated resources and references on metermeta/metricmeta
       * data in cache.
       *
       * Then this object will be reused and no free operation is required.
       */
      pSql->thandle = NULL;
      tscFreeSqlObjPartial(pSql);
      tscTrace("%p sql result is freed by app", pSql);
    }
  } else {
    // if no free resource msg is sent to vnode, we free this object immediately.
    pSql->thandle = NULL;

    if (pSql->fp) {
      assert(pRes->numOfRows == 0 || (pCmd->command > TSDB_SQL_LOCAL));
      tscFreeSqlObj(pSql);
      tscTrace("%p Async sql result is freed by app", pSql);
    } else {
      tscFreeSqlObjPartial(pSql);
      tscTrace("%p sql result is freed", pSql);
    }
  }
}