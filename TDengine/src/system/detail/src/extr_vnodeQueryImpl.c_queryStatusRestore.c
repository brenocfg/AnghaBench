#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  over; int /*<<< orphan*/  lastKey; int /*<<< orphan*/  ekey; int /*<<< orphan*/  skey; } ;
struct TYPE_7__ {int /*<<< orphan*/  pTSBuf; int /*<<< orphan*/  endPos; int /*<<< orphan*/  nextPos; int /*<<< orphan*/  startPos; TYPE_3__* pQuery; } ;
struct TYPE_6__ {int /*<<< orphan*/  cur; int /*<<< orphan*/  end; int /*<<< orphan*/  next; int /*<<< orphan*/  start; int /*<<< orphan*/  overStatus; int /*<<< orphan*/  lastKey; } ;
typedef  TYPE_1__ SQueryStatus ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSKEY ; 
 int /*<<< orphan*/  tsBufSetCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queryStatusRestore(SQueryRuntimeEnv *pRuntimeEnv, SQueryStatus *pStatus) {
  SQuery *pQuery = pRuntimeEnv->pQuery;
  SWAP(pQuery->skey, pQuery->ekey, TSKEY);

  pQuery->lastKey = pStatus->lastKey;

  pQuery->over = pStatus->overStatus;

  pRuntimeEnv->startPos = pStatus->start;
  pRuntimeEnv->nextPos = pStatus->next;
  pRuntimeEnv->endPos = pStatus->end;

  tsBufSetCursor(pRuntimeEnv->pTSBuf, &pStatus->cur);
}