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
struct TYPE_11__ {int /*<<< orphan*/  aOutputBuf; } ;
struct TYPE_10__ {int complete; TYPE_1__* interResultBuf; } ;
struct TYPE_9__ {scalar_t__ stage; scalar_t__ avg; scalar_t__ sum; scalar_t__ num; } ;
typedef  TYPE_1__ SStddevInfo ;
typedef  TYPE_2__ SResultInfo ;
typedef  TYPE_3__ SQLFunctionCtx ;
typedef  TYPE_1__ SAvgInfo ;

/* Variables and functions */
 scalar_t__ GET_DOUBLE_VAL (int /*<<< orphan*/ ) ; 
 TYPE_2__* GET_RES_INFO (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  avg_finalizer (TYPE_3__*) ; 
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static void stddev_next_step(SQLFunctionCtx *pCtx) {
  /*
   * the stddevInfo and the average info struct share the same buffer area
   * And the position of each element in their struct is exactly the same matched
   */
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  SStddevInfo *pStd = pResInfo->interResultBuf;

  if (pStd->stage == 0) {
    /*
     * stddev is calculated in two stage:
     * 1. get the average value of all data;
     * 2. get final result, based on the average values;
     * so, if this routine is in second stage, no further step is required
     */
    pStd->stage++;
    avg_finalizer(pCtx);

    // save average value into tmpBuf, for second stage scan
    SAvgInfo *pAvg = pResInfo->interResultBuf;

    pStd->avg = GET_DOUBLE_VAL(pCtx->aOutputBuf);
    assert((isnan(pAvg->sum) && pAvg->num == 0) || (pStd->num == pAvg->num && pStd->avg == pAvg->sum));
  } else {
    pResInfo->complete = true;
  }
}