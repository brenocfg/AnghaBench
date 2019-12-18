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
struct TYPE_3__ {size_t numOfOutputCols; int* pVisibleCols; scalar_t__ numOfHiddenCols; } ;
typedef  TYPE_1__ SFieldInfo ;

/* Variables and functions */

void tscFieldInfoUpdateVisible(SFieldInfo* pFieldInfo, int32_t index, bool visible) {
  if (index < 0 || index > pFieldInfo->numOfOutputCols) {
    return;
  }

  bool oldVisible = pFieldInfo->pVisibleCols[index];
  pFieldInfo->pVisibleCols[index] = visible;

  if (oldVisible != visible) {
    if (!visible) {
      pFieldInfo->numOfHiddenCols += 1;
    } else {
      if (pFieldInfo->numOfHiddenCols > 0) {
        pFieldInfo->numOfHiddenCols -= 1;
      }
    }
  }
}