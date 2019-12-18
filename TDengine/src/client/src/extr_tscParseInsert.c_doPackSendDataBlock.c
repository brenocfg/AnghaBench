#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pMeterMeta; } ;
struct TYPE_16__ {TYPE_1__** pData; } ;
struct TYPE_15__ {TYPE_6__* pDataBlocks; } ;
struct TYPE_14__ {TYPE_3__ cmd; } ;
struct TYPE_13__ {scalar_t__ pData; } ;
typedef  TYPE_1__ STableDataBlocks ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  int /*<<< orphan*/  SShellSubmitBlock ;
typedef  int /*<<< orphan*/  SMeterMeta ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  tsSetBlockInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int tscCopyDataBlockToPayload (TYPE_2__*,TYPE_1__*) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int tscMergeTableDataBlocks (TYPE_2__*,TYPE_6__*) ; 
 int tscProcessSql (TYPE_2__*) ; 

__attribute__((used)) static int doPackSendDataBlock(SSqlObj *pSql, int32_t numOfRows, STableDataBlocks *pTableDataBlocks) {
  int32_t  code = TSDB_CODE_SUCCESS;
  SSqlCmd *pCmd = &pSql->cmd;

  SMeterMeta *pMeterMeta = tscGetMeterMetaInfo(pCmd, 0)->pMeterMeta;

  SShellSubmitBlock *pBlocks = (SShellSubmitBlock *)(pTableDataBlocks->pData);
  tsSetBlockInfo(pBlocks, pMeterMeta, numOfRows);

  if ((code = tscMergeTableDataBlocks(pSql, pCmd->pDataBlocks)) != TSDB_CODE_SUCCESS) {
    return code;
  }

  // the pDataBlock is different from the pTableDataBlocks
  STableDataBlocks *pDataBlock = pCmd->pDataBlocks->pData[0];
  if ((code = tscCopyDataBlockToPayload(pSql, pDataBlock)) != TSDB_CODE_SUCCESS) {
    return code;
  }

  if ((code = tscProcessSql(pSql)) != TSDB_CODE_SUCCESS) {
    return code;
  }

  return TSDB_CODE_SUCCESS;
}