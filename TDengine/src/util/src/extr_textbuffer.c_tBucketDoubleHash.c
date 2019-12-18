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
struct TYPE_4__ {int dMinVal; double dMaxVal; } ;
struct TYPE_5__ {int nTotalSlots; int nSlotsOfSeg; TYPE_1__ nRange; } ;
typedef  TYPE_2__ tMemBucket ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int DBL_MAX ; 
 int /*<<< orphan*/  pError (char*,int,int) ; 

void tBucketDoubleHash(tMemBucket *pBucket, void *value, int16_t *segIdx, int16_t *slotIdx) {
  double v = *(double *)value;

  if (pBucket->nRange.dMinVal == DBL_MAX) {
    /*
     * taking negative integer into consideration,
     * there is only half of pBucket->segs available for non-negative integer
     */
    double x = DBL_MAX / (pBucket->nTotalSlots >> 1);
    double posx = (v + DBL_MAX) / x;
    *segIdx = ((int32_t)posx) / pBucket->nSlotsOfSeg;
    *slotIdx = ((int32_t)posx) % pBucket->nSlotsOfSeg;
  } else {
    // divide a range of [dMinVal, dMaxVal] into 1024 buckets
    double span = pBucket->nRange.dMaxVal - pBucket->nRange.dMinVal;
    if (span < pBucket->nTotalSlots) {
      int32_t delta = (int32_t)(v - pBucket->nRange.dMinVal);
      *segIdx = delta / pBucket->nSlotsOfSeg;
      *slotIdx = delta % pBucket->nSlotsOfSeg;
    } else {
      double x = span / pBucket->nTotalSlots;
      double posx = (v - pBucket->nRange.dMinVal) / x;
      if (v == pBucket->nRange.dMaxVal) {
        posx -= 1;
      }
      *segIdx = ((int32_t)posx) / pBucket->nSlotsOfSeg;
      *slotIdx = ((int32_t)posx) % pBucket->nSlotsOfSeg;
    }

    if (*segIdx < 0 || *segIdx > 16 || *slotIdx < 0 || *slotIdx > 64) {
      pError("error in hash process. segment is: %d, slot id is: %d\n", *segIdx, *slotIdx);
    }
  }
}