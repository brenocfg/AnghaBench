#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* params; struct TYPE_4__* pData; } ;
typedef  TYPE_1__ STableDataBlocks ;

/* Variables and functions */
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 

void tscDestroyDataBlock(STableDataBlocks* pDataBlock) {
  if (pDataBlock == NULL) {
    return;
  }

  tfree(pDataBlock->pData);
  tfree(pDataBlock->params);
  tfree(pDataBlock);
}