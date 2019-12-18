#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ interResultBuf; } ;
struct TYPE_9__ {scalar_t__ aOutputBuf; int /*<<< orphan*/  outputBytes; int /*<<< orphan*/  outputType; } ;
struct TYPE_8__ {int num; int res; } ;
typedef  TYPE_1__ SStddevInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 TYPE_4__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_4__*) ; 
 int /*<<< orphan*/  setNull (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double sqrt (int) ; 

__attribute__((used)) static void stddev_finalizer(SQLFunctionCtx *pCtx) {
  SStddevInfo *pStd = (SStddevInfo *)GET_RES_INFO(pCtx)->interResultBuf;

  if (pStd->num <= 0) {
    setNull(pCtx->aOutputBuf, pCtx->outputType, pCtx->outputBytes);
  } else {
    double *retValue = (double *)pCtx->aOutputBuf;
    *retValue = sqrt(pStd->res / pStd->num);
    SET_VAL(pCtx, 1, 1);
  }

  resetResultInfo(GET_RES_INFO(pCtx));
}