#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_11__ {int /*<<< orphan*/  pMemBucket; } ;
struct TYPE_10__ {int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_9__ {int /*<<< orphan*/  hasResult; scalar_t__ interResultBuf; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;
typedef  TYPE_3__ SPercentileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 void* GET_INPUT_CHAR_INDEX (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,int,int) ; 
 scalar_t__ isNull (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tMemBucketPut (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void percentile_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  void *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  SPercentileInfo *pInfo = (SPercentileInfo *)pResInfo->interResultBuf;
  tMemBucketPut(pInfo->pMemBucket, pData, 1);

  SET_VAL(pCtx, 1, 1);
  pResInfo->hasResult = DATA_SET_FLAG;
}