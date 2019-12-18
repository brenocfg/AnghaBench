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
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 float DBL_MAX ; 
 scalar_t__ INT16_MAX ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_FLOAT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isNull (float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getStatics_f(int64_t *primaryKey, float *data, int32_t numOfRow, double *min, double *max, double *sum,
                         int16_t *minIndex, int16_t *maxIndex, int32_t *numOfNull) {
  float fmin      = DBL_MAX;
  float fmax      = -DBL_MAX;
  float fminIndex = 0;
  float fmaxIndex = 0;
  double dsum     = 0;

  assert(numOfRow <= INT16_MAX);

  for (int32_t i = 0; i < numOfRow; ++i) {
    if (isNull(&data[i], TSDB_DATA_TYPE_FLOAT)) {
      (*numOfNull) += 1;
      continue;
    }

    float fv = 0;
    *(int32_t*)(&fv) = *(int32_t*)(&(data[i]));

    //*sum += data[i];
    dsum += fv;
    if (fmin > fv) {
      fmin = fv;
      fminIndex = i;
    }

    if (fmax < fv) {
      fmax = fv;
      fmaxIndex = i;
    }

    //    if (isNull(&lastVal, TSDB_DATA_TYPE_FLOAT)) {
    //      lastKey = primaryKey[i];
    //      lastVal = data[i];
    //    } else {
    //      *wsum = lastVal * (primaryKey[i] - lastKey);
    //      lastKey = primaryKey[i];
    //      lastVal = data[i];
    //    }
  }

  double csum = 0;
  *(int64_t*)(&csum) = *(int64_t*)sum;
  csum += dsum;
  *(int64_t*)(sum) = *(int64_t*)(&csum);

  *(int32_t*)max = *(int32_t*)(&fmax);
  *(int32_t*)min = *(int32_t*)(&fmin);
  *(int32_t*)minIndex = *(int32_t*)(&fminIndex);
  *(int32_t*)maxIndex = *(int32_t*)(&fmaxIndex);

}