#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  int /*<<< orphan*/  SInterpolationInfo ;

/* Variables and functions */
 int /*<<< orphan*/  taosGetNumOfResWithoutLimit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t taosGetNumOfResultWithInterpo(SInterpolationInfo* pInterpoInfo, TSKEY* pPrimaryKeyArray,
                                      int32_t numOfRawDataInRows, int64_t nInterval, int64_t ekey,
                                      int32_t maxNumOfRows) {
  int32_t numOfRes = taosGetNumOfResWithoutLimit(pInterpoInfo, pPrimaryKeyArray, numOfRawDataInRows, nInterval, ekey);
  return (numOfRes > maxNumOfRows) ? maxNumOfRows : numOfRes;
}