#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  size_t int16_t ;
struct TYPE_19__ {scalar_t__ numOfFilterCols; size_t numOfCols; scalar_t__ numOfOutputCols; TYPE_7__* colList; TYPE_4__* pSelectExpr; TYPE_3__* pFilterInfo; } ;
struct TYPE_18__ {size_t numOfCols; TYPE_6__* pReqColumns; int /*<<< orphan*/ * pBinExpr; } ;
struct TYPE_15__ {scalar_t__ colId; } ;
struct TYPE_17__ {scalar_t__ colIdxInBuf; int* req; TYPE_5__ data; int /*<<< orphan*/  colIdx; } ;
struct TYPE_16__ {scalar_t__ colId; scalar_t__ colIdxInBuf; } ;
struct TYPE_14__ {TYPE_8__ pBinExprInfo; } ;
struct TYPE_11__ {scalar_t__ colId; } ;
struct TYPE_12__ {scalar_t__ colIdxInBuf; int /*<<< orphan*/  colIdx; TYPE_1__ data; } ;
struct TYPE_13__ {TYPE_2__ info; } ;
typedef  TYPE_8__ SSqlBinaryExprInfo ;
typedef  TYPE_9__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void vnodeUpdateFilterColumnIndex(SQuery* pQuery) {
  for (int32_t i = 0; i < pQuery->numOfFilterCols; ++i) {
    for (int16_t j = 0; j < pQuery->numOfCols; ++j) {
      if (pQuery->pFilterInfo[i].info.data.colId == pQuery->colList[j].data.colId) {
        pQuery->pFilterInfo[i].info.colIdx = pQuery->colList[j].colIdx;
        pQuery->pFilterInfo[i].info.colIdxInBuf = pQuery->colList[j].colIdxInBuf;

        // supplementary scan is also require this column
        pQuery->colList[j].req[1] = 1;
        break;
      }
    }
  }

  // set the column index in buffer for arithmetic operation
  if (pQuery->pSelectExpr != NULL) {
    for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
      SSqlBinaryExprInfo* pBinExprInfo = &pQuery->pSelectExpr[i].pBinExprInfo;
      if (pBinExprInfo->pBinExpr != NULL) {
        for (int16_t j = 0; j < pBinExprInfo->numOfCols; ++j) {
          for (int32_t k = 0; k < pQuery->numOfCols; ++k) {
            if (pBinExprInfo->pReqColumns[j].colId == pQuery->colList[k].data.colId) {
              pBinExprInfo->pReqColumns[j].colIdxInBuf = pQuery->colList[k].colIdxInBuf;
              assert(pQuery->colList[k].colIdxInBuf == k);
              break;
            }
          }
        }
      }
    }
  }
}