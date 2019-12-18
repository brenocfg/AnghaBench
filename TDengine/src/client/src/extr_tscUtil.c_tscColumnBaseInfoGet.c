#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_3__ {size_t numOfCols; int /*<<< orphan*/ * pColList; } ;
typedef  TYPE_1__ SColumnBaseInfo ;
typedef  int /*<<< orphan*/  SColumnBase ;

/* Variables and functions */

SColumnBase* tscColumnBaseInfoGet(SColumnBaseInfo* pColumnBaseInfo, int32_t index) {
  if (pColumnBaseInfo == NULL || pColumnBaseInfo->numOfCols < index) {
    return NULL;
  }

  return &pColumnBaseInfo->pColList[index];
}