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
struct TYPE_5__ {int numOfSlots; scalar_t__* pBuffer; int /*<<< orphan*/ * pBoundingEntries; } ;
typedef  TYPE_1__ tMemBucketSegment ;
struct TYPE_6__ {size_t nSlotsOfSeg; TYPE_1__* pSegs; } ;
typedef  TYPE_2__ tMemBucket ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  MinMaxEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getMinMaxEntryOfNearestSlotInNextSegment (TYPE_2__*,size_t) ; 

__attribute__((used)) static MinMaxEntry getMinMaxEntryOfNextSlotWithData(tMemBucket *pMemBucket, int32_t segIdx, int32_t slotIdx) {
  tMemBucketSegment *pSeg = &pMemBucket->pSegs[segIdx];

  MinMaxEntry next;
  if (slotIdx == pSeg->numOfSlots - 1) {  // find next segment with data
    return getMinMaxEntryOfNearestSlotInNextSegment(pMemBucket, segIdx);
  } else {
    int32_t j = slotIdx + 1;
    for (; j < pMemBucket->nSlotsOfSeg && pMemBucket->pSegs[segIdx].pBuffer[j] == 0; ++j) {
    };

    if (j == pMemBucket->nSlotsOfSeg) {  // current slot has no available
                                         // slot,try next segment
      return getMinMaxEntryOfNearestSlotInNextSegment(pMemBucket, segIdx);
    } else {
      next = pSeg->pBoundingEntries[slotIdx + 1];
      assert(pSeg->pBuffer[slotIdx + 1] != NULL);
    }
  }

  return next;
}