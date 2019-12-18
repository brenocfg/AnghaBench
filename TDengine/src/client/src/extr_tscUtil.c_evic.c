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
typedef  int int32_t ;
struct TYPE_3__ {int numOfOutputCols; int /*<<< orphan*/ * pFields; } ;
typedef  TYPE_1__ SFieldInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void evic(SFieldInfo* pFieldInfo, int32_t index) {
  if (index < pFieldInfo->numOfOutputCols) {
    memmove(&pFieldInfo->pFields[index + 1], &pFieldInfo->pFields[index],
            sizeof(pFieldInfo->pFields[0]) * (pFieldInfo->numOfOutputCols - index));
  }
}