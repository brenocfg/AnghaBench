#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {char* aOutputBuf; int inputBytes; int /*<<< orphan*/  inputType; scalar_t__ hasNull; } ;
struct TYPE_9__ {char hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 char DATA_SET_FLAG ; 
 char* GET_INPUT_CHAR_INDEX (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,int,int) ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minMax_function_f (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void min_function_f(SQLFunctionCtx *pCtx, int32_t index) {
  char *pData = GET_INPUT_CHAR_INDEX(pCtx, index);
  if (pCtx->hasNull && isNull(pData, pCtx->inputType)) {
    return;
  }

  SET_VAL(pCtx, 1, 1);
  minMax_function_f(pCtx, index, 1);

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  if (pResInfo->hasResult == DATA_SET_FLAG) {
    char *flag = pCtx->aOutputBuf + pCtx->inputBytes;
    *flag = DATA_SET_FLAG;
  }
}