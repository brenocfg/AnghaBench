#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFilePage ;
typedef  size_t int32_t ;
struct TYPE_6__ {int nAlloc; int /*<<< orphan*/ * result; TYPE_1__* resultInfo; } ;
struct TYPE_5__ {int bufLen; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SOutputRes ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_1__*) ; 

void clearGroupResultBuf(SOutputRes *pOneOutputRes, int32_t nOutputCols) {
  if (pOneOutputRes == NULL) {
    return;
  }

  for (int32_t i = 0; i < nOutputCols; ++i) {
    SResultInfo *pResInfo = &pOneOutputRes->resultInfo[i];
    int32_t      size = sizeof(tFilePage) + pResInfo->bufLen * pOneOutputRes->nAlloc;

    memset(pOneOutputRes->result[i], 0, (size_t)size);
    resetResultInfo(pResInfo);
  }
}