#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t numOfSlots; TYPE_5__** pBuffer; } ;
typedef  TYPE_2__ tMemBucketSegment ;
struct TYPE_9__ {int numOfElems; size_t numOfSegs; int dataType; TYPE_2__* pSegs; } ;
typedef  TYPE_3__ tMemBucket ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_4__ tFilePage ;
struct TYPE_11__ {int numOfAllElems; int numOfElemsInBuffer; TYPE_1__* pHead; } ;
typedef  TYPE_5__ tExtMemBuffer ;
typedef  double int8_t ;
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
typedef  double int16_t ;
struct TYPE_7__ {TYPE_4__ item; } ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  assert (int) ; 

double findOnlyResult(tMemBucket *pMemBucket) {
  assert(pMemBucket->numOfElems == 1);

  for (int32_t i = 0; i < pMemBucket->numOfSegs; ++i) {
    tMemBucketSegment *pSeg = &pMemBucket->pSegs[i];
    if (pSeg->pBuffer) {
      for (int32_t j = 0; j < pSeg->numOfSlots; ++j) {
        tExtMemBuffer *pBuffer = pSeg->pBuffer[j];
        if (pBuffer) {
          assert(pBuffer->numOfAllElems == 1);
          tFilePage *pPage = &pBuffer->pHead->item;
          if (pBuffer->numOfElemsInBuffer == 1) {
            switch (pMemBucket->dataType) {
              case TSDB_DATA_TYPE_INT:
                return *(int32_t *)pPage->data;
              case TSDB_DATA_TYPE_SMALLINT:
                return *(int16_t *)pPage->data;
              case TSDB_DATA_TYPE_TINYINT:
                return *(int8_t *)pPage->data;
              case TSDB_DATA_TYPE_BIGINT:
                return (double)(*(int64_t *)pPage->data);
              case TSDB_DATA_TYPE_DOUBLE:
                return *(double *)pPage->data;
              case TSDB_DATA_TYPE_FLOAT:
                return *(float *)pPage->data;
              default:
                return 0;
            }
          }
        }
      }
    }
  }
  return 0;
}