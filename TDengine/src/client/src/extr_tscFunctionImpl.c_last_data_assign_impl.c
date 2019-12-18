#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {scalar_t__ hasResult; scalar_t__ ts; } ;
struct TYPE_5__ {scalar_t__ inputBytes; scalar_t__ aOutputBuf; scalar_t__* ptsList; } ;
typedef  TYPE_1__ SQLFunctionCtx ;
typedef  TYPE_2__ SFirstLastInfo ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG ; 
 int /*<<< orphan*/  DO_UPDATE_TAG_COLUMNS (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  pTrace (char*,size_t,scalar_t__,size_t) ; 

__attribute__((used)) static void last_data_assign_impl(SQLFunctionCtx *pCtx, char *pData, int32_t index) {
  int64_t *timestamp = pCtx->ptsList;

  SFirstLastInfo *pInfo = (SFirstLastInfo *)(pCtx->aOutputBuf + pCtx->inputBytes);

  if (pInfo->hasResult != DATA_SET_FLAG || pInfo->ts < timestamp[index]) {
#if defined(_DEBUG_VIEW)
    pTrace("assign index:%d, ts:%lld, val:%d, ", index, timestamp[index], *(int32_t *)pData);
#endif

    memcpy(pCtx->aOutputBuf, pData, pCtx->inputBytes);
    pInfo->hasResult = DATA_SET_FLAG;
    pInfo->ts = timestamp[index];

    DO_UPDATE_TAG_COLUMNS(pCtx, pInfo->ts);
  }
}