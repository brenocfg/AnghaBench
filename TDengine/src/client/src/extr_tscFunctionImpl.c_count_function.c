#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  hasResult; } ;
struct TYPE_8__ {scalar_t__ numOfNull; scalar_t__ isSet; } ;
struct TYPE_9__ {int hasNull; scalar_t__ size; scalar_t__ aOutputBuf; TYPE_1__ preAggVals; int /*<<< orphan*/  inputType; int /*<<< orphan*/  blockStatus; } ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_2__*,scalar_t__) ; 
 TYPE_5__* GET_RES_INFO (TYPE_2__*) ; 
 scalar_t__ IS_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void count_function(SQLFunctionCtx *pCtx) {
  int32_t numOfElem = 0;

  if (IS_DATA_BLOCK_LOADED(pCtx->blockStatus)) {
    /*
     * In following cases, the data block is loaded:
     * 1. A first/last file block for a query
     * 2. Required to handle other queries, such as apercentile/twa/stddev etc.
     * 3. A cache block
     */
    if (pCtx->hasNull) {
      for (int32_t i = 0; i < pCtx->size; ++i) {
        char *val = GET_INPUT_CHAR_INDEX(pCtx, i);
        if (isNull(val, pCtx->inputType)) {
          continue;
        }

        numOfElem += 1;
      }
    } else {
      numOfElem = pCtx->size;
    }
  } else {
    /*
     * 1. column data missing (schema modified) causes pCtx->hasNull == true. pCtx->preAggVals.isSet == true;
     * 2. for general non-primary key columns, pCtx->hasNull may be true or false, pCtx->preAggVals.isSet == true;
     * 3. for primary key column, pCtx->hasNull always be false, pCtx->preAggVals.isSet == false;
     */
    if (pCtx->preAggVals.isSet) {
      numOfElem = pCtx->size - pCtx->preAggVals.numOfNull;
    } else {
      assert(pCtx->hasNull == false);
      numOfElem = pCtx->size;
    }
  }

  if (numOfElem > 0) {
    GET_RES_INFO(pCtx)->hasResult = DATA_SET_FLAG;
  }

  *((int64_t *)pCtx->aOutputBuf) += numOfElem;
  SET_VAL(pCtx, numOfElem, 1);
}