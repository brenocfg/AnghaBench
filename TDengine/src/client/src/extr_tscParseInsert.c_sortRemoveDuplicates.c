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
typedef  int int32_t ;
struct TYPE_5__ {int numOfRows; char* payLoad; } ;
struct TYPE_4__ {int rowSize; int size; scalar_t__ tsSource; int ordered; scalar_t__ pData; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ STableDataBlocks ;
typedef  TYPE_2__ SShellSubmitBlock ;

/* Variables and functions */
 scalar_t__ TSDB_USE_SERVER_TS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  qsort (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rowDataCompar ; 

void sortRemoveDuplicates(STableDataBlocks *dataBuf) {
  SShellSubmitBlock *pBlocks = (SShellSubmitBlock *)dataBuf->pData;

  // size is less than the total size, since duplicated rows may be removed yet.
  assert(pBlocks->numOfRows * dataBuf->rowSize + sizeof(SShellSubmitBlock) == dataBuf->size);

  // if use server time, this block must be ordered
  if (dataBuf->tsSource == TSDB_USE_SERVER_TS) {
    assert(dataBuf->ordered);
  }

  if (!dataBuf->ordered) {
    char *pBlockData = pBlocks->payLoad;
    qsort(pBlockData, pBlocks->numOfRows, dataBuf->rowSize, rowDataCompar);

    int32_t i = 0;
    int32_t j = 1;

    while (j < pBlocks->numOfRows) {
      TSKEY ti = *(TSKEY *)(pBlockData + dataBuf->rowSize * i);
      TSKEY tj = *(TSKEY *)(pBlockData + dataBuf->rowSize * j);

      if (ti == tj) {
        ++j;
        continue;
      }

      int32_t nextPos = (++i);
      if (nextPos != j) {
        memmove(pBlockData + dataBuf->rowSize * nextPos, pBlockData + dataBuf->rowSize * j, dataBuf->rowSize);
      }

      ++j;
    }

    dataBuf->ordered = true;

    pBlocks->numOfRows = i + 1;
    dataBuf->size = sizeof(SShellSubmitBlock) + dataBuf->rowSize * pBlocks->numOfRows;
  }
}