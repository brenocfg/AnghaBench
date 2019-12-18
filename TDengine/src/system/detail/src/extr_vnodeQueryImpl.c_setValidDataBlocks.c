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
struct TYPE_3__ {size_t start; size_t numOfBlocks; int /*<<< orphan*/ ** pBlock; } ;
typedef  TYPE_1__ SMeterDataInfo ;
typedef  int /*<<< orphan*/  SCompBlock ;

/* Variables and functions */
 size_t POINTER_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 char* realloc (int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static bool setValidDataBlocks(SMeterDataInfo *pMeterDataInfo, SCompBlock *pCompBlock, int32_t end) {
  int32_t size = (end - pMeterDataInfo->start) + 1;
  assert(size > 0);

  if (size != pMeterDataInfo->numOfBlocks) {
    char *tmp = realloc(pMeterDataInfo->pBlock, POINTER_BYTES * size);
    if (tmp == NULL) {
      return false;
    }

    pMeterDataInfo->pBlock = (SCompBlock **)tmp;
    pMeterDataInfo->numOfBlocks = size;
  }

  for (int32_t i = pMeterDataInfo->start, j = 0; i <= end; ++i, ++j) {
    pMeterDataInfo->pBlock[j] = &pCompBlock[i];
  }

  return true;
}