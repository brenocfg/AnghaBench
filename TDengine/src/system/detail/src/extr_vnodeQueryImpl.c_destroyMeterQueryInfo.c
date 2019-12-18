#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_4__ {struct TYPE_4__* resultInfo; int /*<<< orphan*/  interResultBuf; struct TYPE_4__* pageList; } ;
typedef  TYPE_1__ SMeterQueryInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 

void destroyMeterQueryInfo(SMeterQueryInfo *pMeterQueryInfo, int32_t numOfCols) {
  if (pMeterQueryInfo == NULL) {
    return;
  }

  free(pMeterQueryInfo->pageList);
  for (int32_t i = 0; i < numOfCols; ++i) {
    tfree(pMeterQueryInfo->resultInfo[i].interResultBuf);
  }

  free(pMeterQueryInfo->resultInfo);
  free(pMeterQueryInfo);
}