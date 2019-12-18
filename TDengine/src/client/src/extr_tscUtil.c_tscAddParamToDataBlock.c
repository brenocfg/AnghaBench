#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int idx; char type; short bytes; int offset; int /*<<< orphan*/  timePrec; } ;
struct TYPE_6__ {int numOfParams; int numOfAllocedParams; TYPE_2__* params; } ;
typedef  TYPE_1__ STableDataBlocks ;
typedef  TYPE_2__ SParamInfo ;

/* Variables and functions */
 void* realloc (TYPE_2__*,int) ; 

SParamInfo* tscAddParamToDataBlock(STableDataBlocks* pDataBlock, char type, uint8_t timePrec, short bytes,
                                   uint32_t offset) {
  uint32_t needed = pDataBlock->numOfParams + 1;
  if (needed > pDataBlock->numOfAllocedParams) {
    needed *= 2;
    void* tmp = realloc(pDataBlock->params, needed * sizeof(SParamInfo));
    if (tmp == NULL) {
      return NULL;
    }
    pDataBlock->params = (SParamInfo*)tmp;
    pDataBlock->numOfAllocedParams = needed;
  }

  SParamInfo* param = pDataBlock->params + pDataBlock->numOfParams;
  param->idx = -1;
  param->type = type;
  param->timePrec = timePrec;
  param->bytes = bytes;
  param->offset = offset;

  ++pDataBlock->numOfParams;
  return param;
}