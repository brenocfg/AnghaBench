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
struct TYPE_4__ {int iMaxVal; int iMinVal; } ;
struct TYPE_5__ {int nTotalSlots; int nSlotsOfSeg; TYPE_1__ nRange; } ;
typedef  TYPE_2__ tMemBucket ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int INT32_MIN ; 

void tBucketIntHash(tMemBucket *pBucket, void *value, int16_t *segIdx, int16_t *slotIdx) {
  int32_t v = *(int32_t *)value;

  if (pBucket->nRange.iMaxVal == INT32_MIN) {
    /*
     * taking negative integer into consideration,
     * there is only half of pBucket->segs available for non-negative integer
     */
    //        int32_t numOfSlots = pBucket->nTotalSlots>>1;
    //        int32_t bits = bitsOfNumber(numOfSlots)-1;

    if (v >= 0) {
      *segIdx = ((v >> (32 - 9)) >> 6) + 8;
      *slotIdx = (v >> (32 - 9)) & 0x3F;
    } else {  // v<0
      *segIdx = ((-v) >> (32 - 9)) >> 6;
      *slotIdx = ((-v) >> (32 - 9)) & 0x3F;
      *segIdx = 7 - (*segIdx);
    }
  } else {
    // divide a range of [iMinVal, iMaxVal] into 1024 buckets
    int32_t span = pBucket->nRange.iMaxVal - pBucket->nRange.iMinVal;
    if (span < pBucket->nTotalSlots) {
      int32_t delta = v - pBucket->nRange.iMinVal;
      *segIdx = delta / pBucket->nSlotsOfSeg;
      *slotIdx = delta % pBucket->nSlotsOfSeg;
    } else {
      double x = (double)span / pBucket->nTotalSlots;
      double posx = (v - pBucket->nRange.iMinVal) / x;
      if (v == pBucket->nRange.iMaxVal) {
        posx -= 1;
      }
      *segIdx = ((int32_t)posx) / pBucket->nSlotsOfSeg;
      *slotIdx = ((int32_t)posx) % pBucket->nSlotsOfSeg;
    }
  }
}