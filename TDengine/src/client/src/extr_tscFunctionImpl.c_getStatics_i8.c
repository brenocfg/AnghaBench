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
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ INT16_MAX ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isNull (char*,scalar_t__) ; 

__attribute__((used)) static void getStatics_i8(int64_t *primaryKey, int32_t type, int8_t *data, int32_t numOfRow, int64_t *min, int64_t *max,
                          int64_t *sum, int16_t *minIndex, int16_t *maxIndex, int32_t *numOfNull) {
  *min = INT64_MAX;
  *max = INT64_MIN;
  *minIndex = 0;
  *maxIndex = 0;

  assert(numOfRow <= INT16_MAX);

  //  int64_t lastKey = 0;
  //  int8_t  lastVal = TSDB_DATA_TINYINT_NULL;

  for (int32_t i = 0; i < numOfRow; ++i) {
    if (isNull((char *)&data[i], type)) {
      (*numOfNull) += 1;
      continue;
    }

    *sum += data[i];
    if (*min > data[i]) {
      *min = data[i];
      *minIndex = i;
    }

    if (*max < data[i]) {
      *max = data[i];
      *maxIndex = i;
    }

    //    if (type != TSDB_DATA_TYPE_BOOL) { // ignore the bool data type pre-calculation
    //      if (isNull((char *)&lastVal, type)) {
    //        lastKey = primaryKey[i];
    //        lastVal = data[i];
    //      } else {
    //        *wsum = lastVal * (primaryKey[i] - lastKey);
    //        lastKey = primaryKey[i];
    //        lastVal = data[i];
    //      }
    //    }
  }
}