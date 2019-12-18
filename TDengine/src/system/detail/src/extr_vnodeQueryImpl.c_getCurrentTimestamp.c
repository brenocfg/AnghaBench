#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_1__ tFilePage ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  size_t int32_t ;
struct TYPE_8__ {int rowIdx; int /*<<< orphan*/  pageIdx; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pInfoEx; int /*<<< orphan*/  pSupporter; TYPE_3__* pPosition; } ;
typedef  TYPE_2__ SCompSupporter ;
typedef  TYPE_3__ Position ;

/* Variables and functions */
 int TSDB_KEYSIZE ; 
 TYPE_1__* getMeterDataPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int64_t getCurrentTimestamp(SCompSupporter *pSupportor, int32_t meterIdx) {
  Position * pPos = &pSupportor->pPosition[meterIdx];
  tFilePage *pPage = getMeterDataPage(pSupportor->pSupporter, pSupportor->pInfoEx[meterIdx], pPos->pageIdx);
  return *(int64_t *)(pPage->data + TSDB_KEYSIZE * pPos->rowIdx);
}