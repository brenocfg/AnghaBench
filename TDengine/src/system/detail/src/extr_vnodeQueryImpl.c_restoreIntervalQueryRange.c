#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ skey; scalar_t__ lastKey; int /*<<< orphan*/  ekey; } ;
struct TYPE_8__ {scalar_t__ skey; scalar_t__ lastKey; int /*<<< orphan*/  ekey; } ;
struct TYPE_7__ {TYPE_2__* pQuery; } ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SMeterQueryInfo ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void restoreIntervalQueryRange(SQueryRuntimeEnv *pRuntimeEnv, SMeterQueryInfo *pMeterQueryInfo) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  pQuery->skey = pMeterQueryInfo->skey;
  pQuery->ekey = pMeterQueryInfo->ekey;
  pQuery->lastKey = pMeterQueryInfo->lastKey;

  assert(((pQuery->lastKey >= pQuery->skey) && QUERY_IS_ASC_QUERY(pQuery)) ||
         ((pQuery->lastKey <= pQuery->skey) && !QUERY_IS_ASC_QUERY(pQuery)));
}