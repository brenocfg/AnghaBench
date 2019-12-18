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
typedef  size_t int32_t ;
struct TYPE_6__ {scalar_t__ numOfFilters; int filterOnBinary; struct TYPE_6__* filterInfo; struct TYPE_6__* pz; } ;
struct TYPE_5__ {scalar_t__ numOfCols; TYPE_2__* pColList; } ;
typedef  TYPE_1__ SColumnBaseInfo ;
typedef  TYPE_2__ SColumnBase ;

/* Variables and functions */
 scalar_t__ TSDB_MAX_COLUMNS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 

void tscColumnBaseInfoDestroy(SColumnBaseInfo* pColumnBaseInfo) {
  if (pColumnBaseInfo == NULL) {
    return;
  }

  assert(pColumnBaseInfo->numOfCols <= TSDB_MAX_COLUMNS);

  for (int32_t i = 0; i < pColumnBaseInfo->numOfCols; ++i) {
    SColumnBase* pColBase = &(pColumnBaseInfo->pColList[i]);

    if (pColBase->numOfFilters > 0) {
      for (int32_t j = 0; j < pColBase->numOfFilters; ++j) {
        assert(pColBase->filterInfo[j].filterOnBinary == 0 || pColBase->filterInfo[j].filterOnBinary == 1);

        if (pColBase->filterInfo[j].filterOnBinary) {
          tfree(pColBase->filterInfo[j].pz);
        }
      }
    }

    tfree(pColBase->filterInfo);
  }

  tfree(pColumnBaseInfo->pColList);
}