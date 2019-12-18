#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_9__ {size_t numOfFilters; TYPE_3__* filterInfo; } ;
struct TYPE_8__ {size_t lowerRelOptr; size_t upperRelOptr; } ;
struct TYPE_6__ {size_t numOfCols; TYPE_4__* pColList; } ;
struct TYPE_7__ {TYPE_1__ colList; } ;
typedef  TYPE_2__ SSqlCmd ;
typedef  TYPE_3__ SColumnFilterInfo ;
typedef  TYPE_4__ SColumnBase ;

/* Variables and functions */
 size_t TSDB_RELATION_INVALID ; 
 size_t TSDB_RELATION_LARGE ; 
 size_t TSDB_RELATION_LARGE_EQUAL ; 
 size_t TSDB_RELATION_LESS ; 
 size_t TSDB_RELATION_LESS_EQUAL ; 

__attribute__((used)) static bool validateFilterExpr(SSqlCmd* pCmd) {
  for (int32_t i = 0; i < pCmd->colList.numOfCols; ++i) {
    SColumnBase* pColBase = &pCmd->colList.pColList[i];

    for (int32_t j = 0; j < pColBase->numOfFilters; ++j) {
      SColumnFilterInfo* pColFilter = &pColBase->filterInfo[j];
      int32_t            lowerOptr = pColFilter->lowerRelOptr;
      int32_t            upperOptr = pColFilter->upperRelOptr;

      if ((lowerOptr == TSDB_RELATION_LARGE_EQUAL || lowerOptr == TSDB_RELATION_LARGE) &&
          (upperOptr == TSDB_RELATION_LESS_EQUAL || upperOptr == TSDB_RELATION_LESS)) {
        continue;
      }

      // there must be at least two range, not support yet.
      if (lowerOptr * upperOptr != TSDB_RELATION_INVALID) {
        return false;
      }
    }
  }

  return true;
}