#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFilePage ;
typedef  size_t int32_t ;
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__ nResultBufSize; TYPE_9__* pResultBuf; TYPE_3__* resColModel; TYPE_2__* pCtx; } ;
struct TYPE_10__ {size_t numOfOutputCols; } ;
struct TYPE_13__ {TYPE_1__ fieldsInfo; } ;
struct TYPE_12__ {int maxCapacity; } ;
struct TYPE_11__ {scalar_t__ aOutputBuf; } ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SLocalReducer ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int tscFieldInfoGetOffset (TYPE_4__*,size_t) ; 

void resetOutputBuf(SSqlCmd *pCmd, SLocalReducer *pLocalReducer) {  // reset output buffer to the beginning
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    pLocalReducer->pCtx[i].aOutputBuf =
        pLocalReducer->pResultBuf->data + tscFieldInfoGetOffset(pCmd, i) * pLocalReducer->resColModel->maxCapacity;
  }

  memset(pLocalReducer->pResultBuf, 0, pLocalReducer->nResultBufSize + sizeof(tFilePage));
}