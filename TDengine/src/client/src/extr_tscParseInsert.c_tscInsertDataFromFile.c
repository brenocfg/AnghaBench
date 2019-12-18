#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_29__ {int rowSize; int /*<<< orphan*/  precision; int /*<<< orphan*/  numOfColumns; } ;
struct TYPE_28__ {TYPE_7__* pMeterMeta; int /*<<< orphan*/  name; } ;
struct TYPE_27__ {int /*<<< orphan*/  numOfCols; } ;
struct TYPE_26__ {TYPE_13__* pDataBlocks; int /*<<< orphan*/  payload; } ;
struct TYPE_23__ {scalar_t__ numOfRows; int /*<<< orphan*/  code; } ;
struct TYPE_25__ {TYPE_1__ res; TYPE_4__ cmd; } ;
struct TYPE_24__ {int size; scalar_t__ nAllocSize; scalar_t__ numOfParams; int rowSize; } ;
struct TYPE_22__ {TYPE_2__** pData; } ;
typedef  TYPE_2__ STableDataBlocks ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;
typedef  int /*<<< orphan*/  SShellSubmitBlock ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_5__ SParsedDataColInfo ;
typedef  TYPE_6__ SMeterMetaInfo ;
typedef  TYPE_7__ SMeterMeta ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_PAYLOAD_SIZE ; 
 int doPackSendDataBlock (TYPE_3__*,int,TYPE_2__*) ; 
 size_t getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtolower (char*,char*) ; 
 int /*<<< orphan*/  tfree (char*) ; 
 int /*<<< orphan*/ * tsGetSchema (TYPE_7__*) ; 
 int tsParseOneRowData (char**,TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tscAllocateMemIfNeed (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tscAppendDataBlock (TYPE_13__*,TYPE_2__*) ; 
 TYPE_13__* tscCreateBlockArrayList () ; 
 TYPE_2__* tscCreateDataBlockEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscSetAssignedColumnInfo (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tscInsertDataFromFile(SSqlObj *pSql, FILE *fp) {
  size_t          readLen = 0;
  char *          line = NULL;
  size_t          n = 0;
  int             len = 0;
  uint32_t        maxRows = 0;
  SSqlCmd *       pCmd = &pSql->cmd;
  int             numOfRows = 0;
  int32_t         code = 0;
  int             nrows = 0;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  SMeterMeta *    pMeterMeta = pMeterMetaInfo->pMeterMeta;
  int32_t         rowSize = pMeterMeta->rowSize;

  pCmd->pDataBlocks = tscCreateBlockArrayList();
  STableDataBlocks *pTableDataBlock =
      tscCreateDataBlockEx(TSDB_PAYLOAD_SIZE, pMeterMeta->rowSize, sizeof(SShellSubmitBlock), pMeterMetaInfo->name);

  tscAppendDataBlock(pCmd->pDataBlocks, pTableDataBlock);

  maxRows = tscAllocateMemIfNeed(pTableDataBlock, rowSize);
  if (maxRows < 1) return -1;

  int                count = 0;
  SParsedDataColInfo spd = {.numOfCols = pMeterMetaInfo->pMeterMeta->numOfColumns};
  SSchema *          pSchema = tsGetSchema(pMeterMetaInfo->pMeterMeta);

  tscSetAssignedColumnInfo(&spd, pSchema, pMeterMetaInfo->pMeterMeta->numOfColumns);

  while ((readLen = getline(&line, &n, fp)) != -1) {
    // line[--readLen] = '\0';
    if (('\r' == line[readLen - 1]) || ('\n' == line[readLen - 1])) line[--readLen] = 0;
    if (readLen <= 0) continue;

    char *lineptr = line;
    strtolower(line, line);

    if (numOfRows >= maxRows || pTableDataBlock->size + pMeterMeta->rowSize >= pTableDataBlock->nAllocSize) {
      uint32_t tSize = tscAllocateMemIfNeed(pTableDataBlock, pMeterMeta->rowSize);
      if (0 == tSize) return (-TSDB_CODE_CLI_OUT_OF_MEMORY);
      maxRows += tSize;    
    }

    len = tsParseOneRowData(&lineptr, pTableDataBlock, pSchema, &spd, pCmd->payload, pMeterMeta->precision);
    if (len <= 0 || pTableDataBlock->numOfParams > 0) {
      pSql->res.code = TSDB_CODE_INVALID_SQL;
      return -1;
    }
    pTableDataBlock->size += len;

    count++;
    nrows++;
    if (count >= maxRows) {
      if ((code = doPackSendDataBlock(pSql, count, pTableDataBlock)) != TSDB_CODE_SUCCESS) {
        return -code;
      }

      pTableDataBlock = pCmd->pDataBlocks->pData[0];
      pTableDataBlock->size = sizeof(SShellSubmitBlock);
      pTableDataBlock->rowSize = pMeterMeta->rowSize;

      numOfRows += pSql->res.numOfRows;
      pSql->res.numOfRows = 0;
      count = 0;
    }
  }

  if (count > 0) {
    if ((code = doPackSendDataBlock(pSql, count, pTableDataBlock)) != TSDB_CODE_SUCCESS) {
      return -code;
    }

    numOfRows += pSql->res.numOfRows;
    pSql->res.numOfRows = 0;
  }

  if (line) tfree(line);

  return numOfRows;
}