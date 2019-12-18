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
struct TYPE_3__ {int numOfFilters; int /*<<< orphan*/ * filterInfo; } ;
typedef  int /*<<< orphan*/  SColumnFilterInfo ;
typedef  TYPE_1__ SColumnBase ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static SColumnFilterInfo* addColumnFilterInfo(SColumnBase* pColumn) {
  if (pColumn == NULL) {
    return NULL;
  }

  int32_t size = pColumn->numOfFilters + 1;
  char*   tmp = realloc(pColumn->filterInfo, sizeof(SColumnFilterInfo) * (size));
  if (tmp != NULL) {
    pColumn->filterInfo = (SColumnFilterInfo*)tmp;
  }

  pColumn->numOfFilters++;

  SColumnFilterInfo* pColFilterInfo = &pColumn->filterInfo[pColumn->numOfFilters - 1];
  memset(pColFilterInfo, 0, sizeof(SColumnFilterInfo));

  return pColFilterInfo;
}