#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  outputBytes; int /*<<< orphan*/  outputType; int /*<<< orphan*/  aOutputBuf; } ;
struct TYPE_7__ {scalar_t__ hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  pTrace (char*) ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  setNull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void function_finalizer(SQLFunctionCtx *pCtx) {
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  if (pResInfo->hasResult != DATA_SET_FLAG) {
    pTrace("no result generated, result is set to NULL");
    setNull(pCtx->aOutputBuf, pCtx->outputType, pCtx->outputBytes);
  }

  resetResultInfo(GET_RES_INFO(pCtx));
}