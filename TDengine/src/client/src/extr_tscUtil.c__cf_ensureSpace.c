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
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__ numOfAlloc; int /*<<< orphan*/ * pColList; } ;
typedef  TYPE_1__ SColumnBaseInfo ;
typedef  int /*<<< orphan*/  SColumnBase ;

/* Variables and functions */
 scalar_t__ TSDB_MAX_COLUMNS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void _cf_ensureSpace(SColumnBaseInfo* pcolList, int32_t size) {
  if (pcolList->numOfAlloc < size) {
    int32_t oldSize = pcolList->numOfAlloc;

    int32_t newSize = (oldSize <= 0) ? 8 : (oldSize << 1);
    while (newSize < size) {
      newSize = (newSize << 1);
    }

    if (newSize > TSDB_MAX_COLUMNS) {
      newSize = TSDB_MAX_COLUMNS;
    }

    int32_t inc = newSize - oldSize;

    pcolList->pColList = realloc(pcolList->pColList, newSize * sizeof(SColumnBase));
    memset(&pcolList->pColList[oldSize], 0, inc * sizeof(SColumnBase));

    pcolList->numOfAlloc = newSize;
  }
}