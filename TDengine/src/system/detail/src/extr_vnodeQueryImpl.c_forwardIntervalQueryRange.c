#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_14__ {scalar_t__ rawEKey; int /*<<< orphan*/  rawSKey; } ;
struct TYPE_11__ {int /*<<< orphan*/  order; } ;
struct TYPE_13__ {scalar_t__ ekey; int nAggTimeInterval; scalar_t__ skey; scalar_t__ lastKey; int /*<<< orphan*/  over; TYPE_1__ order; } ;
struct TYPE_12__ {int /*<<< orphan*/  nextPos; TYPE_3__* pQuery; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SMeterQuerySupportObj ;

/* Variables and functions */
 int GET_FORWARD_DIRECTION_FACTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUERY_COMPLETED ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 int /*<<< orphan*/  QUERY_NO_DATA_TO_CHECK ; 
 scalar_t__ Q_STATUS_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getAlignedIntervalQueryRange (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ loadRequiredBlockIntoMem (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_3__*,int /*<<< orphan*/ ) ; 

void forwardIntervalQueryRange(SMeterQuerySupportObj *pSupporter, SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  int32_t factor = GET_FORWARD_DIRECTION_FACTOR(pQuery->order.order);
  pQuery->ekey += (pQuery->nAggTimeInterval * factor);
  pQuery->skey = pQuery->ekey - (pQuery->nAggTimeInterval - 1) * factor;

  // boundary check
  if (QUERY_IS_ASC_QUERY(pQuery)) {
    if (pQuery->skey > pSupporter->rawEKey) {
      setQueryStatus(pQuery, QUERY_COMPLETED);
      return;
    }

    if (pQuery->ekey > pSupporter->rawEKey) {
      pQuery->ekey = pSupporter->rawEKey;
    }
  } else {
    if (pQuery->skey < pSupporter->rawEKey) {
      setQueryStatus(pQuery, QUERY_COMPLETED);
      return;
    }

    if (pQuery->ekey < pSupporter->rawEKey) {
      pQuery->ekey = pSupporter->rawEKey;
    }
  }

  /* ensure the search in cache will return right position */
  pQuery->lastKey = pQuery->skey;

  TSKEY nextTimestamp = loadRequiredBlockIntoMem(pRuntimeEnv, &pRuntimeEnv->nextPos);
  if ((nextTimestamp > pSupporter->rawEKey && QUERY_IS_ASC_QUERY(pQuery)) ||
      (nextTimestamp < pSupporter->rawEKey && !QUERY_IS_ASC_QUERY(pQuery)) ||
      Q_STATUS_EQUAL(pQuery->over, QUERY_NO_DATA_TO_CHECK)) {
    setQueryStatus(pQuery, QUERY_COMPLETED);
    return;
  }

  // bridge the gap in group by time function
  if ((nextTimestamp > pQuery->ekey && QUERY_IS_ASC_QUERY(pQuery)) ||
      (nextTimestamp < pQuery->ekey && !QUERY_IS_ASC_QUERY(pQuery))) {
    getAlignedIntervalQueryRange(pQuery, nextTimestamp, pSupporter->rawSKey, pSupporter->rawEKey);
  }
}