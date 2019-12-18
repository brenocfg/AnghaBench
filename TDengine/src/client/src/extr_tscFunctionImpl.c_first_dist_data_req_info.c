#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {scalar_t__ hasResult; scalar_t__ ts; } ;
struct TYPE_4__ {scalar_t__ order; int inputBytes; TYPE_2__* aOutputBuf; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SQLFunctionCtx ;
typedef  TYPE_2__ SFirstLastInfo ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_DATA_ALL_NEEDED ; 
 int /*<<< orphan*/  BLK_DATA_NO_NEEDED ; 
 scalar_t__ DATA_SET_FLAG ; 
 scalar_t__ TSQL_SO_DESC ; 

__attribute__((used)) static int32_t first_dist_data_req_info(SQLFunctionCtx *pCtx, TSKEY start, TSKEY end, int32_t colId,
                                        int32_t blockStatus) {
  if (pCtx->order == TSQL_SO_DESC) {
    return BLK_DATA_NO_NEEDED;
  }

  SFirstLastInfo *pInfo = (pCtx->aOutputBuf + pCtx->inputBytes);
  if (pInfo->hasResult != DATA_SET_FLAG) {
    return BLK_DATA_ALL_NEEDED;
  } else {  // data in current block is not earlier than current result
    return (pInfo->ts <= start) ? BLK_DATA_NO_NEEDED : BLK_DATA_ALL_NEEDED;
  }
}