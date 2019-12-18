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
 double DBL_MAX ; 
 scalar_t__ INT16_MAX ; 
 double TSDB_DATA_DOUBLE_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isNull (double*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getStatics_d(int64_t *primaryKey, double *data, int32_t numOfRow, double *min, double *max, double *sum,
                         int16_t *minIndex, int16_t *maxIndex, int32_t *numOfNull) {
  double dmin      = DBL_MAX;
  double dmax      = -DBL_MAX;
  double dminIndex = 0;
  double dmaxIndex = 0;
  double dsum      = 0;

  assert(numOfRow <= INT16_MAX);

  int64_t lastKey = 0;
  double  lastVal = TSDB_DATA_DOUBLE_NULL;

  for (int32_t i = 0; i < numOfRow; ++i) {
    if (isNull(&data[i], TSDB_DATA_TYPE_DOUBLE)) {
      (*numOfNull) += 1;
      continue;
    }

    double dv = 0;
    *(int64_t*)(&dv) = *(int64_t*)(&(data[i]));

    //*sum += data[i];
    dsum += dv;
    if (dmin > dv) {
      dmin = dv;
      dminIndex = i;
    }

    if (dmax < dv) {
      dmax = dv;
      dmaxIndex = i;
    }

    //    if (isNull(&lastVal, TSDB_DATA_TYPE_DOUBLE)) {
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

  *(int64_t*)max = *(int64_t*)(&dmax);
  *(int64_t*)min = *(int64_t*)(&dmin);
  *(int64_t*)minIndex = *(int64_t*)(&dminIndex);
  *(int64_t*)maxIndex = *(int64_t*)(&dmaxIndex);
}