#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nType; scalar_t__ dKey; scalar_t__ i64Key; } ;
struct TYPE_4__ {TYPE_1__ v; } ;
typedef  TYPE_2__ tValuePair ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ TSDB_DATA_TYPE_DOUBLE ; 
 scalar_t__ TSDB_DATA_TYPE_FLOAT ; 

__attribute__((used)) static int32_t resDataAscComparFn(const void *pLeft, const void *pRight) {
  tValuePair *pLeftElem = *(tValuePair **)pLeft;
  tValuePair *pRightElem = *(tValuePair **)pRight;

  int32_t type = pLeftElem->v.nType;
  if (type == TSDB_DATA_TYPE_FLOAT || type == TSDB_DATA_TYPE_DOUBLE) {
    if (pLeftElem->v.dKey == pRightElem->v.dKey) {
      return 0;
    } else {
      return pLeftElem->v.dKey > pRightElem->v.dKey ? 1 : -1;
    }
  } else {
    if (pLeftElem->v.i64Key == pRightElem->v.i64Key) {
      return 0;
    } else {
      return pLeftElem->v.i64Key > pRightElem->v.i64Key ? 1 : -1;
    }
  }
}