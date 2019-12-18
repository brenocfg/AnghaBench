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
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {int /*<<< orphan*/  pMemBucket; } ;
struct TYPE_10__ {scalar_t__ size; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_9__ {int /*<<< orphan*/  hasResult; TYPE_3__* interResultBuf; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;
typedef  TYPE_3__ SPercentileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tMemBucketPut (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void percentile_function(SQLFunctionCtx *pCtx) {
  int32_t notNullElems = 0;

  SResultInfo *    pResInfo = GET_RES_INFO(pCtx);
  SPercentileInfo *pInfo = pResInfo->interResultBuf;

  for (int32_t i = 0; i < pCtx->size; ++i) {
    char *data = GET_INPUT_CHAR_INDEX(pCtx, i);
    if (pCtx->hasNull && isNull(data, pCtx->inputType)) {
      continue;
    }

    notNullElems += 1;
    tMemBucketPut(pInfo->pMemBucket, data, 1);
  }

  SET_VAL(pCtx, notNullElems, 1);
  pResInfo->hasResult = DATA_SET_FLAG;
}