#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tOrderDescriptor ;
typedef  size_t int32_t ;
struct TYPE_6__ {scalar_t__ groupOrderType; int /*<<< orphan*/  numOfElems; TYPE_2__** pLocalData; int /*<<< orphan*/ * pDesc; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int rowIdx; TYPE_1__ filePage; } ;
typedef  TYPE_2__ SLocalDataSource ;
typedef  TYPE_3__ SCompareParam ;

/* Variables and functions */
 scalar_t__ TSQL_SO_DESC ; 
 size_t compare_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t compare_d (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int32_t treeComparator(const void *pLeft, const void *pRight, void *param) {
  int32_t pLeftIdx = *(int32_t *)pLeft;
  int32_t pRightIdx = *(int32_t *)pRight;

  SCompareParam *    pParam = (SCompareParam *)param;
  tOrderDescriptor * pDesc = pParam->pDesc;
  SLocalDataSource **pLocalData = pParam->pLocalData;

  /* this input is exhausted, set the special value to denote this */
  if (pLocalData[pLeftIdx]->rowIdx == -1) {
    return 1;
  }

  if (pLocalData[pRightIdx]->rowIdx == -1) {
    return -1;
  }

  if (pParam->groupOrderType == TSQL_SO_DESC) {  // desc
    return compare_d(pDesc, pParam->numOfElems, pLocalData[pLeftIdx]->rowIdx, pLocalData[pLeftIdx]->filePage.data,
                     pParam->numOfElems, pLocalData[pRightIdx]->rowIdx, pLocalData[pRightIdx]->filePage.data);
  } else {
    return compare_a(pDesc, pParam->numOfElems, pLocalData[pLeftIdx]->rowIdx, pLocalData[pLeftIdx]->filePage.data,
                     pParam->numOfElems, pLocalData[pRightIdx]->rowIdx, pLocalData[pRightIdx]->filePage.data);
  }
}