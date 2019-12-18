#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_10__ {size_t numOfCols; TYPE_2__* colList; } ;
struct TYPE_7__ {scalar_t__ colId; } ;
struct TYPE_9__ {TYPE_1__ colInfo; } ;
struct TYPE_8__ {scalar_t__ colId; } ;
typedef  TYPE_3__ SSqlFuncExprMsg ;
typedef  TYPE_4__ SQueryMeterMsg ;

/* Variables and functions */

__attribute__((used)) static int32_t getColumnIndexInSource(SQueryMeterMsg* pQueryMsg, SSqlFuncExprMsg* pExprMsg) {
  int32_t j = 0;

  while(j < pQueryMsg->numOfCols) {
    if (pExprMsg->colInfo.colId == pQueryMsg->colList[j].colId) {
      break;
    }

    j += 1;
  }

  return j;
}