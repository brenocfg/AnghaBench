#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ nSize; int /*<<< orphan*/ ** pData; } ;
struct TYPE_16__ {int batchSize; int vnodeIdx; TYPE_6__* pDataBlocks; } ;
struct TYPE_14__ {int code; scalar_t__ qhandle; scalar_t__ numOfTotal; scalar_t__ numOfRows; } ;
struct TYPE_15__ {int /*<<< orphan*/ * thandle; TYPE_2__ res; TYPE_4__ cmd; } ;
struct TYPE_13__ {TYPE_3__* pSql; } ;
typedef  TYPE_1__ STscStmt ;
typedef  int /*<<< orphan*/  STableDataBlocks ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;

/* Variables and functions */
 int TSDB_CODE_INVALID_VALUE ; 
 int TSDB_CODE_SUCCESS ; 
 int tscCopyDataBlockToPayload (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* tscDestroyBlockArrayList (TYPE_6__*) ; 
 int /*<<< orphan*/  tscDoQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  tscFreeSqlObjPartial (TYPE_3__*) ; 
 int tscMergeTableDataBlocks (TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static int insertStmtExecute(STscStmt* stmt) {
  SSqlCmd* pCmd = &stmt->pSql->cmd;
  if (pCmd->batchSize == 0) {
    return TSDB_CODE_INVALID_VALUE;
  }
  if ((pCmd->batchSize % 2) == 1) {
    ++pCmd->batchSize;
  }

  if (pCmd->pDataBlocks->nSize > 0) {
    // merge according to vgid
    int code = tscMergeTableDataBlocks(stmt->pSql, pCmd->pDataBlocks);
    if (code != TSDB_CODE_SUCCESS) {
      return code;
    }

    STableDataBlocks *pDataBlock = pCmd->pDataBlocks->pData[0];
    code = tscCopyDataBlockToPayload(stmt->pSql, pDataBlock);
    if (code != TSDB_CODE_SUCCESS) {
      return code;
    }

    // set the next sent data vnode index in data block arraylist
    pCmd->vnodeIdx = 1;
  } else {
    pCmd->pDataBlocks = tscDestroyBlockArrayList(pCmd->pDataBlocks);
  }

  SSqlObj *pSql = stmt->pSql;
  SSqlRes *pRes = &pSql->res;
  pRes->numOfRows = 0;
  pRes->numOfTotal = 0;
  pRes->qhandle = 0;
  pSql->thandle = NULL;

  tscDoQuery(pSql);

  // tscTrace("%p SQL result:%d, %s pObj:%p", pSql, pRes->code, taos_errstr(taos), pObj);
  if (pRes->code != TSDB_CODE_SUCCESS) {
    tscFreeSqlObjPartial(pSql);
  }

  return pRes->code;
}