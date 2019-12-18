#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {int rowsInFileBlock; } ;
struct TYPE_16__ {TYPE_1__ cfg; } ;
struct TYPE_15__ {size_t vnode; } ;
struct TYPE_13__ {scalar_t__ rowSize; scalar_t__ numOfOutputCols; TYPE_3__** sdata; TYPE_2__* pSelectExpr; } ;
struct TYPE_14__ {scalar_t__ bufIndex; TYPE_4__ query; TYPE_6__* pObj; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {scalar_t__ resBytes; } ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SQInfo ;
typedef  TYPE_6__ SMeterObj ;

/* Variables and functions */
 scalar_t__ EXTRA_BYTES ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memmove (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ tsCompressMsgSize ; 
 scalar_t__ tsCompressString (char*,scalar_t__,int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* vnodeList ; 

__attribute__((used)) static void doCopyQueryResultToMsg(SQInfo *pQInfo, int32_t numOfRows, char* data, int32_t* size) {
  SMeterObj* pObj = pQInfo->pObj;
  SQuery* pQuery = &pQInfo->query;

  int tnumOfRows = vnodeList[pObj->vnode].cfg.rowsInFileBlock;
  int32_t dataSize = pQInfo->query.rowSize * numOfRows;

  if (dataSize >= tsCompressMsgSize && tsCompressMsgSize > 0) {
    char* compBuf = malloc((size_t) dataSize);

    // for metric query, bufIndex always be 0.
    char* d = compBuf;
    for (int32_t col = 0; col < pQuery->numOfOutputCols; ++col) {  // pQInfo->bufIndex == 0
      int32_t bytes = pQuery->pSelectExpr[col].resBytes;

      memmove(d, pQuery->sdata[col]->data + bytes * tnumOfRows * pQInfo->bufIndex, bytes * numOfRows);
      d += bytes * numOfRows;
    }

    *size = tsCompressString(compBuf, dataSize, 1, data, dataSize + EXTRA_BYTES, 0, 0, 0);

    dTrace("QInfo:%p compress rsp msg, before:%d, after:%d", pQInfo, dataSize, *size);
    free(compBuf);
  } else { // for metric query, bufIndex always be 0.
    for (int32_t col = 0; col < pQuery->numOfOutputCols; ++col) {  // pQInfo->bufIndex == 0
      int32_t bytes = pQuery->pSelectExpr[col].resBytes;

      memmove(data, pQuery->sdata[col]->data + bytes * tnumOfRows * pQInfo->bufIndex, bytes * numOfRows);
      data += bytes * numOfRows;
    }
  }
}