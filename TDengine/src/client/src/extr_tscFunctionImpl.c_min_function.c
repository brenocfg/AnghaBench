#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {int inputBytes; void** aOutputBuf; } ;
struct TYPE_8__ {scalar_t__ superTableQ; void* hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 void* DATA_SET_FLAG ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,scalar_t__,int) ; 
 int /*<<< orphan*/  minMax_function (TYPE_2__*,void**,int,scalar_t__*) ; 

__attribute__((used)) static void min_function(SQLFunctionCtx *pCtx) {
  int32_t notNullElems = 0;
  minMax_function(pCtx, pCtx->aOutputBuf, 1, &notNullElems);

  SET_VAL(pCtx, notNullElems, 1);

  if (notNullElems > 0) {
    SResultInfo *pResInfo = GET_RES_INFO(pCtx);
    pResInfo->hasResult = DATA_SET_FLAG;

    // set the flag for super table query
    if (pResInfo->superTableQ) {
      *(pCtx->aOutputBuf + pCtx->inputBytes) = DATA_SET_FLAG;
    }
  }
}