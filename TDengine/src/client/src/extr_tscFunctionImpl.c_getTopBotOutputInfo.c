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
struct TYPE_7__ {scalar_t__ currentStage; int /*<<< orphan*/ * aOutputBuf; } ;
struct TYPE_6__ {int /*<<< orphan*/ * interResultBuf; scalar_t__ superTableQ; } ;
typedef  int /*<<< orphan*/  STopBotInfo ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 scalar_t__ SECONDARY_STAGE_MERGE ; 

__attribute__((used)) static STopBotInfo *getTopBotOutputInfo(SQLFunctionCtx *pCtx) {
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  // only the first_stage_merge is directly written data into final output buffer
  if (pResInfo->superTableQ && pCtx->currentStage != SECONDARY_STAGE_MERGE) {
    return pCtx->aOutputBuf;
  } else {  // for normal table query and super table at the secondary_stage, result is written to intermediate buffer
    return pResInfo->interResultBuf;
  }
}