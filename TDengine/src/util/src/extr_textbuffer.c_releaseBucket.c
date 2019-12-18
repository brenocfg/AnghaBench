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
struct TYPE_4__ {size_t numOfSlots; int /*<<< orphan*/ ** pBuffer; } ;
typedef  TYPE_1__ tMemBucketSegment ;
struct TYPE_5__ {size_t numOfSegs; TYPE_1__* pSegs; } ;
typedef  TYPE_2__ tMemBucket ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  tExtMemBufferDestroy (int /*<<< orphan*/ **) ; 

void releaseBucket(tMemBucket *pMemBucket, int32_t segIdx, int32_t slotIdx) {
  if (segIdx < 0 || segIdx > pMemBucket->numOfSegs || slotIdx < 0) {
    return;
  }

  tMemBucketSegment *pSeg = &pMemBucket->pSegs[segIdx];
  if (slotIdx < 0 || slotIdx >= pSeg->numOfSlots || pSeg->pBuffer[slotIdx] == NULL) {
    return;
  }

  tExtMemBufferDestroy(&pSeg->pBuffer[slotIdx]);
}