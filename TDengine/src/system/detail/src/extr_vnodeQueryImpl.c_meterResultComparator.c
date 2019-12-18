#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ tFilePage ;
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_7__ {int pageIdx; int rowIdx; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pInfoEx; int /*<<< orphan*/  pSupporter; TYPE_3__* pPosition; } ;
typedef  TYPE_2__ SCompSupporter ;
typedef  TYPE_3__ Position ;

/* Variables and functions */
 int TSDB_KEYSIZE ; 
 TYPE_1__* getMeterDataPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int32_t meterResultComparator(const void *pLeft, const void *pRight, void *param) {
  int32_t left = *(int32_t *)pLeft;
  int32_t right = *(int32_t *)pRight;

  SCompSupporter *supportor = (SCompSupporter *)param;

  Position leftPos = supportor->pPosition[left];
  Position rightPos = supportor->pPosition[right];

  /* left source is exhausted */
  if (leftPos.pageIdx == -1 && leftPos.rowIdx == -1) {
    return 1;
  }

  /* right source is exhausted*/
  if (rightPos.pageIdx == -1 && rightPos.rowIdx == -1) {
    return -1;
  }

  tFilePage *pPageLeft = getMeterDataPage(supportor->pSupporter, supportor->pInfoEx[left], leftPos.pageIdx);
  int64_t    leftTimestamp = *(int64_t *)(pPageLeft->data + TSDB_KEYSIZE * leftPos.rowIdx);

  tFilePage *pPageRight = getMeterDataPage(supportor->pSupporter, supportor->pInfoEx[right], rightPos.pageIdx);
  int64_t    rightTimestamp = *(int64_t *)(pPageRight->data + TSDB_KEYSIZE * rightPos.rowIdx);

  if (leftTimestamp == rightTimestamp) {
    return 0;
  }

  return leftTimestamp > rightTimestamp ? 1 : -1;
}