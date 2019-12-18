#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_16__ {int /*<<< orphan*/  tagInfo; int /*<<< orphan*/  inputType; int /*<<< orphan*/ * ptsList; TYPE_1__* param; scalar_t__ hasNull; } ;
struct TYPE_15__ {int /*<<< orphan*/  hasResult; } ;
struct TYPE_14__ {scalar_t__ num; } ;
struct TYPE_13__ {int /*<<< orphan*/  i64Key; } ;
typedef  TYPE_2__ STopBotInfo ;
typedef  TYPE_3__ SResultInfo ;
typedef  TYPE_4__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_4__*,size_t) ; 
 TYPE_3__* GET_RES_INFO (TYPE_4__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_top_function_add (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* getTopBotOutputInfo (TYPE_4__*) ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void top_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  char *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  STopBotInfo *pRes = getTopBotOutputInfo(pCtx);
  assert(pRes->num >= 0);

  SET_VAL(pCtx, 1, 1);
  do_top_function_add(pRes, pCtx->param[0].i64Key, pData, pCtx->ptsList[index], pCtx->inputType, &pCtx->tagInfo, NULL,
                      0);

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  pResInfo->hasResult = DATA_SET_FLAG;
}