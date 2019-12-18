#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  nSize; } ;

/* Variables and functions */
 int MAX (scalar_t__,scalar_t__) ; 
 size_t TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  TSDB_DATA_TYPE_INT ; 
 scalar_t__ TSQL_SO_ASC ; 
 scalar_t__ isNull (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setNull (char*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* tDataTypeDesc ; 

void calc_fn_i32_i32_div(void *left, void *right, int32_t numLeft, int32_t numRight, void *output, int32_t order) {
  int32_t *pLeft = (int32_t *)left;
  int32_t *pRight = (int32_t *)right;
  double * pOutput = (double *)output;

  int32_t i = (order == TSQL_SO_ASC) ? 0 : MAX(numLeft, numRight) - 1;
  int32_t step = (order == TSQL_SO_ASC) ? 1 : -1;

  if (numLeft == numRight) {
    for (; i >= 0 && i < numRight; i += step, pOutput += step) {
      if (isNull((char *)&(pLeft[i]), TSDB_DATA_TYPE_INT) || isNull((char *)&(pRight[i]), TSDB_DATA_TYPE_INT)) {
        setNull((char *)(pOutput), TSDB_DATA_TYPE_DOUBLE, tDataTypeDesc[TSDB_DATA_TYPE_DOUBLE].nSize);
        continue;
      }

      *pOutput = (double)pLeft[i] / pRight[i];
    }
  } else if (numLeft == 1) {
    for (; i >= 0 && i < numRight; i += step, pOutput += step) {
      if (isNull((char *)(pLeft), TSDB_DATA_TYPE_INT) || isNull((char *)&(pRight[i]), TSDB_DATA_TYPE_INT)) {
        setNull((char *)pOutput, TSDB_DATA_TYPE_DOUBLE, tDataTypeDesc[TSDB_DATA_TYPE_DOUBLE].nSize);
        continue;
      }

      *pOutput = (double)pLeft[0] / pRight[i];
    }
  } else if (numRight == 1) {
    for (; i >= 0 && i < numLeft; i += step, pOutput += step) {
      if (isNull((char *)&(pLeft[i]), TSDB_DATA_TYPE_INT) || isNull((char *)(pRight), TSDB_DATA_TYPE_INT)) {
        setNull((char *)pOutput, TSDB_DATA_TYPE_DOUBLE, tDataTypeDesc[TSDB_DATA_TYPE_DOUBLE].nSize);
        continue;
      }
      *pOutput = (double)pLeft[i] / pRight[0];
    }
  }
}