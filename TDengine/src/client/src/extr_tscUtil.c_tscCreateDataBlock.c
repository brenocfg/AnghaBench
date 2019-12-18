#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int nAllocSize; int ordered; int /*<<< orphan*/  prevTS; scalar_t__ pData; } ;
typedef  TYPE_1__ STableDataBlocks ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MIN ; 
 scalar_t__ calloc (int,int) ; 

STableDataBlocks* tscCreateDataBlock(int32_t size) {
  STableDataBlocks* dataBuf = (STableDataBlocks*)calloc(1, sizeof(STableDataBlocks));
  dataBuf->nAllocSize = (uint32_t)size;
  dataBuf->pData = calloc(1, dataBuf->nAllocSize);
  dataBuf->ordered = true;
  dataBuf->prevTS = INT64_MIN;
  return dataBuf;
}