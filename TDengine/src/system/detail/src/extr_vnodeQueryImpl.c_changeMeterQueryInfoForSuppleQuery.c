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
struct TYPE_4__ {int order; int vnodeIndex; } ;
struct TYPE_5__ {scalar_t__ numOfPages; int reverseFillRes; int /*<<< orphan*/  numOfRes; int /*<<< orphan*/  reverseIndex; TYPE_1__ cur; scalar_t__ queryRangeSet; void* skey; void* lastKey; void* ekey; } ;
typedef  void* TSKEY ;
typedef  TYPE_2__ SMeterQueryInfo ;

/* Variables and functions */

void changeMeterQueryInfoForSuppleQuery(SMeterQueryInfo *pMeterQueryInfo, TSKEY skey, TSKEY ekey) {
  if (pMeterQueryInfo == NULL) {
    return;
  }

  pMeterQueryInfo->skey = skey;
  pMeterQueryInfo->ekey = ekey;
  pMeterQueryInfo->lastKey = pMeterQueryInfo->skey;

  pMeterQueryInfo->queryRangeSet = 0;
  pMeterQueryInfo->cur.order = pMeterQueryInfo->cur.order ^ 1;
  pMeterQueryInfo->cur.vnodeIndex = -1;

  // previous does not generate any results
  if (pMeterQueryInfo->numOfPages == 0) {
    pMeterQueryInfo->reverseFillRes = 0;
  } else {
    pMeterQueryInfo->reverseIndex = pMeterQueryInfo->numOfRes;
    pMeterQueryInfo->reverseFillRes = 1;
  }
}