#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {scalar_t__ pointsToRead; scalar_t__ pointsRead; scalar_t__ numOfOutputCols; TYPE_2__** sdata; } ;
struct TYPE_10__ {TYPE_1__* pCtx; TYPE_4__* pQuery; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {scalar_t__ outputBytes; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_4__*) ; 
 scalar_t__ isTSCompQuery (TYPE_4__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

void moveDescOrderResultsToFront(SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *pQuery = pRuntimeEnv->pQuery;
  int32_t maxrows = pQuery->pointsToRead;

  if (QUERY_IS_ASC_QUERY(pQuery) || isTSCompQuery(pQuery)) {
    return;
  }

  if (pQuery->pointsRead > 0 && pQuery->pointsRead < maxrows) {
    for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
      int32_t bytes = pRuntimeEnv->pCtx[i].outputBytes;
      memmove(pQuery->sdata[i]->data, pQuery->sdata[i]->data + (maxrows - pQuery->pointsRead) * bytes,
              pQuery->pointsRead * bytes);
    }
  }
}