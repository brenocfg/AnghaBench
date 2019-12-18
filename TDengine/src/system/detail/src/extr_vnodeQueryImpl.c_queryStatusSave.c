#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int order; } ;
struct TYPE_14__ {TYPE_1__ cur; } ;
struct TYPE_13__ {int /*<<< orphan*/  skey; int /*<<< orphan*/  lastKey; int /*<<< orphan*/  ekey; int /*<<< orphan*/  over; } ;
struct TYPE_12__ {int /*<<< orphan*/  endPos; int /*<<< orphan*/  startPos; TYPE_5__* pTSBuf; int /*<<< orphan*/  nextPos; TYPE_4__* pQuery; } ;
struct TYPE_11__ {int /*<<< orphan*/  cur; int /*<<< orphan*/  end; int /*<<< orphan*/  next; int /*<<< orphan*/  start; int /*<<< orphan*/  lastKey; int /*<<< orphan*/  overStatus; } ;
typedef  TYPE_2__ SQueryStatus ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSKEY ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufGetCursor (TYPE_5__*) ; 
 int /*<<< orphan*/  tsBufNextPos (TYPE_5__*) ; 

__attribute__((used)) static void queryStatusSave(SQueryRuntimeEnv *pRuntimeEnv, SQueryStatus *pStatus) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  pStatus->overStatus = pQuery->over;
  pStatus->lastKey = pQuery->lastKey;

  pStatus->start = pRuntimeEnv->startPos;
  pStatus->next = pRuntimeEnv->nextPos;
  pStatus->end = pRuntimeEnv->endPos;

  pStatus->cur = tsBufGetCursor(pRuntimeEnv->pTSBuf);  // save the cursor

  if (pRuntimeEnv->pTSBuf) {
    pRuntimeEnv->pTSBuf->cur.order ^= 1;
    tsBufNextPos(pRuntimeEnv->pTSBuf);
  }

  setQueryStatus(pQuery, QUERY_NOT_COMPLETED);

  SWAP(pQuery->skey, pQuery->ekey, TSKEY);
  pQuery->lastKey = pQuery->skey;
  pRuntimeEnv->startPos = pRuntimeEnv->endPos;
}