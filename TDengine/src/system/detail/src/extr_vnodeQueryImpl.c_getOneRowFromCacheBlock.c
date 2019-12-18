#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_17__ {scalar_t__ numOfPoints; scalar_t__* offset; } ;
struct TYPE_16__ {scalar_t__ colId; scalar_t__ bytes; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {scalar_t__ numOfColumns; TYPE_6__* schema; } ;
struct TYPE_14__ {scalar_t__ numOfCols; TYPE_2__* colList; } ;
struct TYPE_13__ {TYPE_4__* pQuery; } ;
struct TYPE_11__ {scalar_t__ colId; } ;
struct TYPE_12__ {scalar_t__ colIdx; TYPE_1__ data; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SMeterObj ;
typedef  TYPE_6__ SColumn ;
typedef  TYPE_7__ SCacheBlock ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setNull (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void getOneRowFromCacheBlock(SQueryRuntimeEnv *pRuntimeEnv, SMeterObj *pMeterObj, SCacheBlock *pBlock,
                                    char **dst, int32_t pos) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  /*
   * in case of cache block expired, the pos may exceed the number of points in block, so check
   * the range in the first place.
   */
  if (pos > pBlock->numOfPoints) {
    pos = pBlock->numOfPoints;
  }

  for (int32_t i = 0; i < pQuery->numOfCols; ++i) {
    int32_t colIdx = pQuery->colList[i].colIdx;
    int32_t colId = pQuery->colList[i].data.colId;

    SColumn *pCols = &pMeterObj->schema[colIdx];

    if (colIdx < 0 || colIdx >= pMeterObj->numOfColumns || pCols->colId != colId) {  // set null
      setNull(dst[i], pCols->type, pCols->bytes);
    } else {
      memcpy(dst[i], pBlock->offset[colIdx] + pos * pCols->bytes, pCols->bytes);
    }
  }
}