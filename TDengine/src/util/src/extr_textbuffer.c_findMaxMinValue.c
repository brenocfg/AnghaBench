#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t numOfSlots; TYPE_1__* pBoundingEntries; int /*<<< orphan*/ * pBuffer; } ;
typedef  TYPE_2__ tMemBucketSegment ;
struct TYPE_7__ {size_t numOfSegs; int dataType; TYPE_2__* pSegs; } ;
typedef  TYPE_3__ tMemBucket ;
typedef  size_t int32_t ;
struct TYPE_5__ {double iMinVal; double iMaxVal; double dMinVal; double dMaxVal; scalar_t__ i64MaxVal; scalar_t__ i64MinVal; } ;

/* Variables and functions */
 double DBL_MAX ; 
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 

__attribute__((used)) static void findMaxMinValue(tMemBucket *pMemBucket, double *maxVal, double *minVal) {
  *minVal = DBL_MAX;
  *maxVal = -DBL_MAX;

  for (int32_t i = 0; i < pMemBucket->numOfSegs; ++i) {
    tMemBucketSegment *pSeg = &pMemBucket->pSegs[i];
    if (pSeg->pBuffer == NULL) {
      continue;
    }
    switch (pMemBucket->dataType) {
      case TSDB_DATA_TYPE_INT:
      case TSDB_DATA_TYPE_SMALLINT:
      case TSDB_DATA_TYPE_TINYINT: {
        for (int32_t j = 0; j < pSeg->numOfSlots; ++j) {
          double minv = pSeg->pBoundingEntries[j].iMinVal;
          double maxv = pSeg->pBoundingEntries[j].iMaxVal;

          if (*minVal > minv) {
            *minVal = minv;
          }
          if (*maxVal < maxv) {
            *maxVal = maxv;
          }
        }
        break;
      }
      case TSDB_DATA_TYPE_DOUBLE:
      case TSDB_DATA_TYPE_FLOAT: {
        for (int32_t j = 0; j < pSeg->numOfSlots; ++j) {
          double minv = pSeg->pBoundingEntries[j].dMinVal;
          double maxv = pSeg->pBoundingEntries[j].dMaxVal;

          if (*minVal > minv) {
            *minVal = minv;
          }
          if (*maxVal < maxv) {
            *maxVal = maxv;
          }
        }
        break;
      }
      case TSDB_DATA_TYPE_BIGINT: {
        for (int32_t j = 0; j < pSeg->numOfSlots; ++j) {
          double minv = (double)pSeg->pBoundingEntries[j].i64MinVal;
          double maxv = (double)pSeg->pBoundingEntries[j].i64MaxVal;

          if (*minVal > minv) {
            *minVal = minv;
          }
          if (*maxVal < maxv) {
            *maxVal = maxv;
          }
        }
        break;
      }
    }
  }
}