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
typedef  int /*<<< orphan*/  tExtMemBuffer ;
typedef  size_t int32_t ;
typedef  size_t int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  tExtMemBufferDestroy (int /*<<< orphan*/ **) ; 

tExtMemBuffer *releaseBucketsExceptFor(tMemBucket *pMemBucket, int16_t segIdx, int16_t slotIdx) {
  tExtMemBuffer *pBuffer = NULL;

  for (int32_t i = 0; i < pMemBucket->numOfSegs; ++i) {
    tMemBucketSegment *pSeg = &pMemBucket->pSegs[i];

    for (int32_t j = 0; j < pSeg->numOfSlots; ++j) {
      if (i == segIdx && j == slotIdx) {
        pBuffer = pSeg->pBuffer[j];
      } else {
        if (pSeg->pBuffer && pSeg->pBuffer[j]) {
          tExtMemBufferDestroy(&pSeg->pBuffer[j]);
        }
      }
    }
  }

  return pBuffer;
}