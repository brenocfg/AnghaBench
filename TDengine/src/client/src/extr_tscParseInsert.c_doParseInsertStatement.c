#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_20__ {int /*<<< orphan*/  vgid; int /*<<< orphan*/  rowSize; int /*<<< orphan*/  uid; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; TYPE_6__* pMeterMeta; } ;
struct TYPE_18__ {int idx; int offset; } ;
struct TYPE_17__ {int /*<<< orphan*/  numOfParams; int /*<<< orphan*/  payload; int /*<<< orphan*/  pDataBlocks; } ;
struct TYPE_16__ {TYPE_3__ cmd; } ;
struct TYPE_15__ {scalar_t__ numOfParams; int numOfMeters; int /*<<< orphan*/  vgid; scalar_t__ pData; TYPE_4__* params; } ;
typedef  TYPE_1__ STableDataBlocks ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  int /*<<< orphan*/  SShellSubmitBlock ;
typedef  int /*<<< orphan*/  SParsedDataColInfo ;
typedef  TYPE_4__ SParamInfo ;
typedef  TYPE_5__ SMeterMetaInfo ;
typedef  TYPE_6__ SMeterMeta ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_DEFAULT_PAYLOAD_SIZE ; 
 scalar_t__ tsParseValues (char**,TYPE_1__*,TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsSetBlockInfo (int /*<<< orphan*/ *,TYPE_6__*,scalar_t__) ; 
 scalar_t__ tscAllocateMemIfNeed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tscGetDataBlockFromList (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t doParseInsertStatement(SSqlObj *pSql, void *pTableHashList, char **str, SParsedDataColInfo *spd,
                                      int32_t *totalNum) {
  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  SMeterMeta *    pMeterMeta = pMeterMetaInfo->pMeterMeta;

  STableDataBlocks *dataBuf =
      tscGetDataBlockFromList(pTableHashList, pCmd->pDataBlocks, pMeterMeta->uid, TSDB_DEFAULT_PAYLOAD_SIZE,
                              sizeof(SShellSubmitBlock), pMeterMeta->rowSize, pMeterMetaInfo->name);

  int32_t maxNumOfRows = tscAllocateMemIfNeed(dataBuf, pMeterMeta->rowSize);
  if (0 == maxNumOfRows) {
    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  }

  int32_t numOfRows = tsParseValues(str, dataBuf, pMeterMeta, maxNumOfRows, spd, pCmd->payload);
  if (numOfRows <= 0) {
    return TSDB_CODE_INVALID_SQL;
  }

  for (uint32_t i = 0; i < dataBuf->numOfParams; ++i) {
    SParamInfo* param = dataBuf->params + i;
    if (param->idx == -1) {
      param->idx = pCmd->numOfParams++;
      param->offset -= sizeof(SShellSubmitBlock);
    }
  }

  SShellSubmitBlock *pBlocks = (SShellSubmitBlock *)(dataBuf->pData);
  tsSetBlockInfo(pBlocks, pMeterMeta, numOfRows);

  dataBuf->vgid = pMeterMeta->vgid;
  dataBuf->numOfMeters = 1;

  /*
   * the value of pRes->numOfRows does not affect the true result of AFFECTED ROWS,
   * which is actually returned from server.
   */
  *totalNum += numOfRows;
  return TSDB_CODE_SUCCESS;
}