#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ order; int numOfRawDataInRows; scalar_t__ startTimestamp; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SInterpolationInfo ;

/* Variables and functions */
 scalar_t__ INTERPOL_IS_ASC_INTERPOL (TYPE_1__*) ; 
 scalar_t__ TSQL_SO_ASC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ labs (scalar_t__) ; 

int32_t taosGetNumOfResWithoutLimit(SInterpolationInfo* pInterpoInfo, int64_t* pPrimaryKeyArray,
                                    int32_t numOfAvailRawData, int64_t nInterval, int64_t ekey) {
  if (numOfAvailRawData > 0) {
    int32_t finalNumOfResult = 0;

    if (pInterpoInfo->order == TSQL_SO_ASC) {
      // get last timestamp, calculate the result size
      int64_t lastKey = pPrimaryKeyArray[pInterpoInfo->numOfRawDataInRows - 1];
      finalNumOfResult = (int32_t)((lastKey - pInterpoInfo->startTimestamp) / nInterval) + 1;
    } else {  // todo error less than one!!!
      TSKEY lastKey = pPrimaryKeyArray[0];
      finalNumOfResult = (int32_t)((pInterpoInfo->startTimestamp - lastKey) / nInterval) + 1;
    }

    assert(finalNumOfResult >= numOfAvailRawData);
    return finalNumOfResult;
  } else {
    /* reach the end of data */
    if ((ekey < pInterpoInfo->startTimestamp && INTERPOL_IS_ASC_INTERPOL(pInterpoInfo)) ||
        (ekey > pInterpoInfo->startTimestamp && !INTERPOL_IS_ASC_INTERPOL(pInterpoInfo))) {
      return 0;
    } else {
      return (int32_t)(labs(ekey - pInterpoInfo->startTimestamp) / nInterval) + 1;
    }
  }
}