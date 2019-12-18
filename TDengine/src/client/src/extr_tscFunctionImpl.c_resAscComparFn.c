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
struct TYPE_2__ {scalar_t__ timestamp; } ;
typedef  TYPE_1__ tValuePair ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int32_t resAscComparFn(const void *pLeft, const void *pRight) {
  tValuePair *pLeftElem = *(tValuePair **)pLeft;
  tValuePair *pRightElem = *(tValuePair **)pRight;

  if (pLeftElem->timestamp == pRightElem->timestamp) {
    return 0;
  } else {
    return pLeftElem->timestamp > pRightElem->timestamp ? 1 : -1;
  }
}