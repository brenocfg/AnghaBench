#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {size_t numOfCols; TYPE_2__* pColList; } ;
struct TYPE_5__ {int /*<<< orphan*/  tableIndex; } ;
struct TYPE_6__ {TYPE_1__ colIndex; } ;
typedef  TYPE_3__ SColumnBaseInfo ;

/* Variables and functions */

void tscColumnBaseInfoUpdateTableIndex(SColumnBaseInfo* pColList, int16_t tableIndex) {
  for (int32_t i = 0; i < pColList->numOfCols; ++i) {
    pColList->pColList[i].colIndex.tableIndex = tableIndex;
  }
}