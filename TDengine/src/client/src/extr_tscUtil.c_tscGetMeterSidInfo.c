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
struct TYPE_3__ {size_t numOfSids; int* pSidExtInfoList; } ;
typedef  TYPE_1__ SVnodeSidList ;
typedef  int /*<<< orphan*/  SMeterSidExtInfo ;

/* Variables and functions */
 int /*<<< orphan*/  tscError (char*,...) ; 

SMeterSidExtInfo* tscGetMeterSidInfo(SVnodeSidList* pSidList, int32_t idx) {
  if (pSidList == NULL) {
    tscError("illegal sidlist");
    return 0;
  }

  if (idx < 0 || idx >= pSidList->numOfSids) {
    int32_t sidRange = (pSidList->numOfSids > 0) ? (pSidList->numOfSids - 1) : 0;

    tscError("illegal sidIdx:%d, reset to 0, sidIdx range:%d-%d", idx, 0, sidRange);
    idx = 0;
  }
  return (SMeterSidExtInfo*)(pSidList->pSidExtInfoList[idx] + (char*)pSidList);
}