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
typedef  double int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ DBL_EPSILON ; 
 scalar_t__ fabs (double) ; 

__attribute__((used)) static int32_t compareDoubleIntVal(const void* pLeft, const void* pRight) {
  double ret = (*(double*)pLeft) - (*(int64_t*)pRight);
  if (fabs(ret) < DBL_EPSILON) {
    return 0;
  } else {
    return ret > 0 ? 1 : -1;
  }
}