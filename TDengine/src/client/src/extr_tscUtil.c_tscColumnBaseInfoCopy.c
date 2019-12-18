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
typedef  size_t int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_8__ {int numOfAlloc; size_t numOfCols; TYPE_2__* pColList; } ;
struct TYPE_6__ {scalar_t__ tableIndex; } ;
struct TYPE_7__ {int numOfFilters; int /*<<< orphan*/ * filterInfo; TYPE_1__ colIndex; } ;
typedef  int /*<<< orphan*/  SColumnFilterInfo ;
typedef  TYPE_3__ SColumnBaseInfo ;
typedef  int /*<<< orphan*/  SColumnBase ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  tscColumnFilterInfoCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void tscColumnBaseInfoCopy(SColumnBaseInfo* dst, const SColumnBaseInfo* src, int16_t tableIndex) {
  if (src == NULL) {
    return;
  }

  *dst = *src;
  dst->pColList = calloc(1, sizeof(SColumnBase) * dst->numOfAlloc);

  int16_t num = 0;
  for (int32_t i = 0; i < src->numOfCols; ++i) {
    if (src->pColList[i].colIndex.tableIndex == tableIndex || tableIndex < 0) {
      dst->pColList[num] = src->pColList[i];

      if (dst->pColList[num].numOfFilters > 0) {
        dst->pColList[num].filterInfo = calloc(1, dst->pColList[num].numOfFilters * sizeof(SColumnFilterInfo));

        for (int32_t j = 0; j < dst->pColList[num].numOfFilters; ++j) {
          tscColumnFilterInfoCopy(&dst->pColList[num].filterInfo[j], &src->pColList[i].filterInfo[j]);
        }
      }

      num += 1;
    }
  }

  dst->numOfCols = num;
}