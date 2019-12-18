#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {scalar_t__ numOfFilterCols; int checkBufferInLoop; scalar_t__ pointsOffset; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pTSBuf; TYPE_2__* pQuery; } ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;

/* Variables and functions */
 scalar_t__ isTSCompQuery (TYPE_2__*) ; 
 scalar_t__ isTopBottomQuery (TYPE_2__*) ; 

__attribute__((used)) static int32_t reviseForwardSteps(SQueryRuntimeEnv *pRuntimeEnv, int32_t forwardStep) {
  /*
   * 1. If value filter exists, we try all data in current block, and do not set the QUERY_RESBUF_FULL flag.
   *
   * 2. In case of top/bottom/ts_comp query, the checkBufferInLoop == 1 and pQuery->numOfFilterCols
   * may be 0 or not. We do not check the capacity of output buffer, since the filter function will do it.
   *
   * 3. In handling the query of secondary query of join, tsBuf servers as a ts filter.
   */
  SQuery *pQuery = pRuntimeEnv->pQuery;

  if (isTopBottomQuery(pQuery) || isTSCompQuery(pQuery) || pQuery->numOfFilterCols > 0 || pRuntimeEnv->pTSBuf != NULL) {
    return forwardStep;
  }

  // current buffer does not have enough space, try in the next loop
  if ((pQuery->checkBufferInLoop == 1) && (pQuery->pointsOffset <= forwardStep)) {
    forwardStep = pQuery->pointsOffset;
  }

  return forwardStep;
}