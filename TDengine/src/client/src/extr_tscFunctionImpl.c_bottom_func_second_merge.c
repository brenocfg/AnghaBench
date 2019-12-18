#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_22__ {int /*<<< orphan*/  currentStage; int /*<<< orphan*/  tagInfo; int /*<<< orphan*/  outputType; TYPE_1__* param; } ;
struct TYPE_21__ {int /*<<< orphan*/  hasResult; } ;
struct TYPE_20__ {size_t num; TYPE_3__** res; } ;
struct TYPE_18__ {int /*<<< orphan*/  i64Key; } ;
struct TYPE_19__ {int /*<<< orphan*/  pTags; int /*<<< orphan*/  timestamp; TYPE_2__ v; } ;
struct TYPE_17__ {int /*<<< orphan*/  i64Key; } ;
typedef  TYPE_4__ STopBotInfo ;
typedef  TYPE_5__ SResultInfo ;
typedef  TYPE_6__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 scalar_t__ GET_INPUT_CHAR (TYPE_6__*) ; 
 TYPE_5__* GET_RES_INFO (TYPE_6__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_6__*,size_t,size_t) ; 
 int /*<<< orphan*/  buildTopBotStruct (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  do_bottom_function_add (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* getTopBotOutputInfo (TYPE_6__*) ; 

__attribute__((used)) static void bottom_func_second_merge(SQLFunctionCtx *pCtx) {
  STopBotInfo *pInput = (STopBotInfo *)GET_INPUT_CHAR(pCtx);

  // construct the input data struct from binary data
  buildTopBotStruct(pInput, pCtx);

  STopBotInfo *pOutput = getTopBotOutputInfo(pCtx);

  // the intermediate result is binary, we only use the output data type
  for (int32_t i = 0; i < pInput->num; ++i) {
    do_bottom_function_add(pOutput, pCtx->param[0].i64Key, &pInput->res[i]->v.i64Key, pInput->res[i]->timestamp,
                           pCtx->outputType, &pCtx->tagInfo, pInput->res[i]->pTags, pCtx->currentStage);
  }

  SET_VAL(pCtx, pInput->num, pOutput->num);

  if (pOutput->num > 0) {
    SResultInfo *pResInfo = GET_RES_INFO(pCtx);
    pResInfo->hasResult = DATA_SET_FLAG;
  }
}