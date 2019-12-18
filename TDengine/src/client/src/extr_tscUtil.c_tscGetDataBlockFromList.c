#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  STableDataBlocks ;
typedef  int /*<<< orphan*/  SDataBlockList ;

/* Variables and functions */
 scalar_t__ taosAddIntHash (void*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ taosGetIntHashData (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscAppendDataBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tscCreateDataBlockEx (size_t,scalar_t__,scalar_t__,char*) ; 

STableDataBlocks* tscGetDataBlockFromList(void* pHashList, SDataBlockList* pDataBlockList, int64_t id, int32_t size,
                                          int32_t startOffset, int32_t rowSize, char* tableId) {
  STableDataBlocks* dataBuf = NULL;

  STableDataBlocks** t1 = (STableDataBlocks**)taosGetIntHashData(pHashList, id);
  if (t1 != NULL) {
    dataBuf = *t1;
  }

  if (dataBuf == NULL) {
    dataBuf = tscCreateDataBlockEx((size_t)size, rowSize, startOffset, tableId);
    dataBuf = *(STableDataBlocks**)taosAddIntHash(pHashList, id, (char*)&dataBuf);
    tscAppendDataBlock(pDataBlockList, dataBuf);
  }

  return dataBuf;
}