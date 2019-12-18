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

/* Type definitions */
struct TYPE_17__ {void* compress; int /*<<< orphan*/  useconds; int /*<<< orphan*/  offset; void* precision; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_16__ {int type; } ;
struct TYPE_14__ {scalar_t__ numOfRows; scalar_t__ offset; scalar_t__ row; void* useconds; void* precision; scalar_t__ pRsp; } ;
struct TYPE_15__ {int /*<<< orphan*/ * thandle; int /*<<< orphan*/  vnode; int /*<<< orphan*/  ip; TYPE_1__* pTscObj; TYPE_4__ cmd; TYPE_2__ res; } ;
struct TYPE_13__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SRetrieveMeterRsp ;

/* Variables and functions */
 int TSDB_QUERY_TYPE_FREE_RESOURCE ; 
 int /*<<< orphan*/  doDecompressPayload (TYPE_4__*,TYPE_2__*,void*) ; 
 void* htobe64 (int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 void* htons (void*) ; 
 int /*<<< orphan*/  taosAddConnIntoCache (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscConnCache ; 
 scalar_t__ tscProjectionQueryOnMetric (TYPE_4__*) ; 
 int /*<<< orphan*/  tscSetResultPointer (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,scalar_t__,scalar_t__) ; 

int tscProcessRetrieveRspFromVnode(SSqlObj *pSql) {
  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;

  SRetrieveMeterRsp *pRetrieve = (SRetrieveMeterRsp *)pRes->pRsp;

  pRes->numOfRows = htonl(pRetrieve->numOfRows);
  pRes->precision = htons(pRetrieve->precision);
  pRes->offset = htobe64(pRetrieve->offset);

  pRes->useconds = htobe64(pRetrieve->useconds);
  pRetrieve->compress = htons(pRetrieve->compress);

  doDecompressPayload(pCmd, pRes, pRetrieve->compress);

  tscSetResultPointer(pCmd, pRes);
  pRes->row = 0;

  /**
   * If the query result is exhausted, the connection will be recycled.
   * If current query is to free resource at server side, the connection will be recycle.
   */
  if ((pRes->numOfRows == 0 && !(tscProjectionQueryOnMetric(pCmd) && pRes->offset > 0)) ||
      ((pCmd->type & TSDB_QUERY_TYPE_FREE_RESOURCE) == TSDB_QUERY_TYPE_FREE_RESOURCE)) {
    taosAddConnIntoCache(tscConnCache, pSql->thandle, pSql->ip, pSql->vnode, pObj->user);
    pSql->thandle = NULL;
  } else {
    tscTrace("%p numOfRows:%d, offset:%d, not recycle connection", pSql, pRes->numOfRows, pRes->offset);
  }

  return 0;
}