#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_16__ {int idx; } ;
struct TYPE_15__ {size_t numOfRows; } ;
struct TYPE_14__ {int batchSize; TYPE_2__* pDataBlocks; } ;
struct TYPE_13__ {size_t size; size_t nAllocSize; char* pData; size_t numOfParams; TYPE_7__* params; } ;
struct TYPE_12__ {TYPE_1__* pSql; } ;
struct TYPE_11__ {size_t nSize; TYPE_4__** pData; } ;
struct TYPE_10__ {TYPE_5__ cmd; } ;
typedef  int /*<<< orphan*/  TAOS_BIND ;
typedef  TYPE_3__ STscStmt ;
typedef  TYPE_4__ STableDataBlocks ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SShellSubmitBlock ;
typedef  TYPE_7__ SParamInfo ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int doBindParam (char*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 void* realloc (char*,size_t) ; 
 int /*<<< orphan*/  tscTrace (char*,int) ; 

__attribute__((used)) static int insertStmtBindParam(STscStmt* stmt, TAOS_BIND* bind) {
  SSqlCmd* pCmd = &stmt->pSql->cmd;

  int32_t alloced = 1, binded = 0;
  if (pCmd->batchSize > 0) {
    alloced = (pCmd->batchSize + 1) / 2;
    binded = pCmd->batchSize / 2;
  }

  for (int32_t i = 0; i < pCmd->pDataBlocks->nSize; ++i) {
    STableDataBlocks* pBlock = pCmd->pDataBlocks->pData[i];
    uint32_t          totalDataSize = pBlock->size - sizeof(SShellSubmitBlock);
    uint32_t          dataSize = totalDataSize / alloced;
    assert(dataSize * alloced == totalDataSize);

    if (alloced == binded) {
      totalDataSize += dataSize + sizeof(SShellSubmitBlock);
      if (totalDataSize > pBlock->nAllocSize) {
        const double factor = 1.5;
        void* tmp = realloc(pBlock->pData, (uint32_t)(totalDataSize * factor));
        if (tmp == NULL) {
          return TSDB_CODE_CLI_OUT_OF_MEMORY;
        }
        pBlock->pData = (char*)tmp;
        pBlock->nAllocSize = (uint32_t)(totalDataSize * factor);
      }
    }

    char* data = pBlock->pData + sizeof(SShellSubmitBlock) + dataSize * binded;
    for (uint32_t j = 0; j < pBlock->numOfParams; ++j) {
      SParamInfo* param = pBlock->params + j;
      int code = doBindParam(data, param, bind + param->idx);
      if (code != TSDB_CODE_SUCCESS) {
        tscTrace("param %d: type mismatch or invalid", param->idx);
        return code;
      }
    }
  }

  // actual work of all data blocks is done, update block size and numOfRows.
  // note we don't do this block by block during the binding process, because 
  // we cannot recover if something goes wrong.
  pCmd->batchSize = binded * 2 + 1;

  if (binded < alloced) {
    return TSDB_CODE_SUCCESS;
  }

  for (int32_t i = 0; i < pCmd->pDataBlocks->nSize; ++i) {
    STableDataBlocks* pBlock = pCmd->pDataBlocks->pData[i];

    uint32_t totalDataSize = pBlock->size - sizeof(SShellSubmitBlock);
    pBlock->size += totalDataSize / alloced;

    SShellSubmitBlock* pSubmit = (SShellSubmitBlock*)pBlock->pData;
    pSubmit->numOfRows += pSubmit->numOfRows / alloced;
  }

  return TSDB_CODE_SUCCESS;
}