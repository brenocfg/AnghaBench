#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int /*<<< orphan*/  numOfPoints; } ;
struct TYPE_10__ {size_t numOfColumns; TYPE_1__* schema; } ;
struct TYPE_9__ {TYPE_2__** colDataBuffer; TYPE_4__* pMeterObj; } ;
struct TYPE_8__ {char* data; } ;
struct TYPE_7__ {size_t colId; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SMeterObj ;
typedef  TYPE_5__ SCacheBlock ;

/* Variables and functions */
 char* doGetDataBlockImpl (char*,size_t,int) ; 
 int /*<<< orphan*/  setNullN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *doGetDataBlocks(bool isDiskFileBlock, SQueryRuntimeEnv *pRuntimeEnv, char *data, int32_t colIdx,
                             int32_t colId, int16_t type, int16_t bytes, int32_t tmpBufIndex) {
  char *pData = NULL;

  if (isDiskFileBlock) {
    pData = doGetDataBlockImpl(data, colIdx, isDiskFileBlock);
  } else {
    SCacheBlock *pCacheBlock = (SCacheBlock *)data;
    SMeterObj *  pMeter = pRuntimeEnv->pMeterObj;

    if (colIdx < 0 || pMeter->numOfColumns <= colIdx || pMeter->schema[colIdx].colId != colId) {
      // data in cache is not current available, we need fill the data block in null value
      pData = pRuntimeEnv->colDataBuffer[tmpBufIndex]->data;
      setNullN(pData, type, bytes, pCacheBlock->numOfPoints);
    } else {
      pData = doGetDataBlockImpl(data, colIdx, isDiskFileBlock);
    }
  }

  return pData;
}