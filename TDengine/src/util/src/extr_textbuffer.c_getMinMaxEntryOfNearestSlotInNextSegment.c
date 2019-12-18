#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ numOfSlots; int /*<<< orphan*/ * pBoundingEntries; int /*<<< orphan*/ ** pBuffer; } ;
typedef  TYPE_1__ tMemBucketSegment ;
struct TYPE_5__ {size_t numOfSegs; size_t nSlotsOfSeg; TYPE_1__* pSegs; } ;
typedef  TYPE_2__ tMemBucket ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  MinMaxEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static MinMaxEntry getMinMaxEntryOfNearestSlotInNextSegment(tMemBucket *pMemBucket, int32_t segIdx) {
  int32_t i = segIdx + 1;
  while (i < pMemBucket->numOfSegs && pMemBucket->pSegs[i].numOfSlots == 0) ++i;

  tMemBucketSegment *pSeg = &pMemBucket->pSegs[i];
  assert(pMemBucket->numOfSegs > i && pMemBucket->pSegs[i].pBuffer != NULL);

  i = 0;
  while (i < pMemBucket->nSlotsOfSeg && pSeg->pBuffer[i] == NULL) ++i;

  assert(i < pMemBucket->nSlotsOfSeg);
  return pSeg->pBoundingEntries[i];
}