#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t int32_t ;
struct TYPE_5__ {size_t nSize; TYPE_1__** pData; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ nAllocSize; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ STableDataBlocks ;
typedef  TYPE_2__ SDataBlockList ;

/* Variables and functions */
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,scalar_t__) ; 

void tscFreeUnusedDataBlocks(SDataBlockList* pList) {
  /* release additional memory consumption */
  for (int32_t i = 0; i < pList->nSize; ++i) {
    STableDataBlocks* pDataBlock = pList->pData[i];
    pDataBlock->pData = realloc(pDataBlock->pData, pDataBlock->size);
    pDataBlock->nAllocSize = (uint32_t)pDataBlock->size;
  }
}