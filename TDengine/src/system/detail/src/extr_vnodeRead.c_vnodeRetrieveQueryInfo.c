#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_12__ {int /*<<< orphan*/  precision; } ;
struct TYPE_16__ {TYPE_1__ cfg; } ;
struct TYPE_14__ {int rowSize; int /*<<< orphan*/ * sdata; } ;
struct TYPE_15__ {int code; int pointsRead; int pointsReturned; TYPE_2__* pObj; int /*<<< orphan*/  dataReady; scalar_t__ killed; int /*<<< orphan*/  signature; TYPE_3__ query; } ;
struct TYPE_13__ {size_t vnode; } ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SQInfo ;

/* Variables and functions */
 int TSDB_CODE_INVALID_QHANDLE ; 
 int TSDB_CODE_QUERY_CANCELLED ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  dError (char*,TYPE_4__*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_4__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeIsQInfoValid (TYPE_4__*) ; 
 TYPE_5__* vnodeList ; 

int vnodeRetrieveQueryInfo(void *handle, int *numOfRows, int *rowSize, int16_t *timePrec) {
  SQInfo *pQInfo;
  SQuery *pQuery;

  *numOfRows = 0;
  *rowSize = 0;

  pQInfo = (SQInfo *)handle;
  if (pQInfo == NULL) {
    return TSDB_CODE_INVALID_QHANDLE;
  }

  pQuery = &(pQInfo->query);
  if (!vnodeIsQInfoValid(pQInfo) || (pQuery->sdata == NULL)) {
    dError("QInfo:%p %p retrieve memory is corrupted!!! QInfo:%p, sign:%p, sdata:%p", pQInfo, pQuery, pQInfo,
           pQInfo->signature, pQuery->sdata);
    return TSDB_CODE_INVALID_QHANDLE;
  }

  if (pQInfo->killed) {
    dTrace("QInfo:%p it is already killed, %p, code:%d", pQInfo, pQuery, pQInfo->code);
    if (pQInfo->code == TSDB_CODE_SUCCESS) {
      return TSDB_CODE_QUERY_CANCELLED;
    } else { // in case of not TSDB_CODE_SUCCESS, return the code to client
      return pQInfo->code;
    }
  }

  sem_wait(&pQInfo->dataReady);
  *numOfRows = pQInfo->pointsRead - pQInfo->pointsReturned;
  *rowSize = pQuery->rowSize;

  *timePrec = vnodeList[pQInfo->pObj->vnode].cfg.precision;

  if (pQInfo->code < 0) return -pQInfo->code;

  return TSDB_CODE_SUCCESS;
}