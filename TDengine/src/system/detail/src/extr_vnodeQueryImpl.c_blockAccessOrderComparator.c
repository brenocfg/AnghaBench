#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {size_t* blockIndexArray; size_t* numOfBlocksPerMeter; TYPE_3__** pDataBlockInfoEx; } ;
struct TYPE_6__ {TYPE_1__* compBlock; } ;
struct TYPE_7__ {TYPE_2__ pBlock; } ;
struct TYPE_5__ {scalar_t__ offset; scalar_t__ last; } ;
typedef  TYPE_3__ SMeterDataBlockInfoEx ;
typedef  TYPE_4__ SBlockOrderSupporter ;

/* Variables and functions */
 int /*<<< orphan*/  dError (char*,scalar_t__) ; 

__attribute__((used)) static int32_t blockAccessOrderComparator(const void *pLeft, const void *pRight, void *param) {
  int32_t leftTableIndex = *(int32_t *)pLeft;
  int32_t rightTableIndex = *(int32_t *)pRight;

  SBlockOrderSupporter *pSupporter = (SBlockOrderSupporter *)param;

  int32_t leftTableBlockIndex = pSupporter->blockIndexArray[leftTableIndex];
  int32_t rightTableBlockIndex = pSupporter->blockIndexArray[rightTableIndex];

  if (leftTableBlockIndex > pSupporter->numOfBlocksPerMeter[leftTableIndex]) {
    /* left block is empty */
    return 1;
  } else if (rightTableBlockIndex > pSupporter->numOfBlocksPerMeter[rightTableIndex]) {
    /* right block is empty */
    return -1;
  }

  SMeterDataBlockInfoEx *pLeftBlockInfoEx = &pSupporter->pDataBlockInfoEx[leftTableIndex][leftTableBlockIndex];
  SMeterDataBlockInfoEx *pRightBlockInfoEx = &pSupporter->pDataBlockInfoEx[rightTableIndex][rightTableBlockIndex];

  //    assert(pLeftBlockInfoEx->pBlock.compBlock->offset != pRightBlockInfoEx->pBlock.compBlock->offset);
  if (pLeftBlockInfoEx->pBlock.compBlock->offset == pRightBlockInfoEx->pBlock.compBlock->offset &&
      pLeftBlockInfoEx->pBlock.compBlock->last == pRightBlockInfoEx->pBlock.compBlock->last) {
    // todo add more information
    dError("error in header file, two block with same offset:%p", pLeftBlockInfoEx->pBlock.compBlock->offset);
  }

  return pLeftBlockInfoEx->pBlock.compBlock->offset > pRightBlockInfoEx->pBlock.compBlock->offset ? 1 : -1;
}