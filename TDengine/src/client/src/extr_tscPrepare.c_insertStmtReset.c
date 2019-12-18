#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_13__ {size_t numOfRows; } ;
struct TYPE_12__ {int batchSize; scalar_t__ vnodeIdx; TYPE_2__* pDataBlocks; } ;
struct TYPE_11__ {int size; scalar_t__ pData; } ;
struct TYPE_10__ {TYPE_1__* pSql; } ;
struct TYPE_9__ {size_t nSize; TYPE_4__** pData; } ;
struct TYPE_8__ {TYPE_5__ cmd; } ;
typedef  TYPE_3__ STscStmt ;
typedef  TYPE_4__ STableDataBlocks ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SShellSubmitBlock ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 

__attribute__((used)) static int insertStmtReset(STscStmt* pStmt) {
  SSqlCmd* pCmd = &pStmt->pSql->cmd;
  if (pCmd->batchSize > 2) {
    int32_t alloced = (pCmd->batchSize + 1) / 2;
    for (int32_t i = 0; i < pCmd->pDataBlocks->nSize; ++i) {
      STableDataBlocks* pBlock = pCmd->pDataBlocks->pData[i];

      uint32_t totalDataSize = pBlock->size - sizeof(SShellSubmitBlock);
      pBlock->size = sizeof(SShellSubmitBlock) + totalDataSize / alloced;

      SShellSubmitBlock* pSubmit = (SShellSubmitBlock*)pBlock->pData;
      pSubmit->numOfRows = pSubmit->numOfRows / alloced;
    }
  }
  pCmd->batchSize = 0;
  pCmd->vnodeIdx = 0;
  return TSDB_CODE_SUCCESS;
}