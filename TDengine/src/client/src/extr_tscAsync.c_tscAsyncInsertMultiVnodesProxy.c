#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {scalar_t__ nSize; int /*<<< orphan*/ * pData; } ;
struct TYPE_10__ {scalar_t__ vnodeIdx; TYPE_3__* pDataBlocks; int /*<<< orphan*/  isInsertFromFile; } ;
struct TYPE_9__ {int /*<<< orphan*/  param; int /*<<< orphan*/  (* fp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* fetchFp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;struct TYPE_9__* signature; TYPE_2__ cmd; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SSqlCmd ;
typedef  TYPE_3__ SDataBlockList ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tscCopyDataBlockToPayload (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tscDestroyBlockArrayList (TYPE_3__*) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_1__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_1__*,...) ; 

void tscAsyncInsertMultiVnodesProxy(void *param, TAOS_RES *tres, int numOfRows) {
  SSqlObj *pSql = (SSqlObj *)param;
  SSqlCmd *pCmd = &pSql->cmd;
  int32_t  code = TSDB_CODE_SUCCESS;

  assert(!pCmd->isInsertFromFile && pSql->signature == pSql);

  SDataBlockList *pDataBlocks = pCmd->pDataBlocks;
  if (pDataBlocks == NULL || pCmd->vnodeIdx >= pDataBlocks->nSize) {
    // restore user defined fp
    pSql->fp = pSql->fetchFp;
    tscTrace("%p Async insertion completed, destroy data block list", pSql);

    // release data block data
    pCmd->pDataBlocks = tscDestroyBlockArrayList(pCmd->pDataBlocks);

    // all data has been sent to vnode, call user function
    (*pSql->fp)(pSql->param, tres, numOfRows);
  } else {
    do {
      code = tscCopyDataBlockToPayload(pSql, pDataBlocks->pData[pCmd->vnodeIdx++]);
      if (code != TSDB_CODE_SUCCESS) {
        tscTrace("%p prepare submit data block failed in async insertion, vnodeIdx:%d, total:%d, code:%d",
                 pSql, pCmd->vnodeIdx - 1, pDataBlocks->nSize, code);
      }

    } while (code != TSDB_CODE_SUCCESS && pCmd->vnodeIdx < pDataBlocks->nSize);

    // build submit msg may fail
    if (code == TSDB_CODE_SUCCESS) {
      tscTrace("%p async insertion, vnodeIdx:%d, total:%d", pSql, pCmd->vnodeIdx - 1, pDataBlocks->nSize);
      tscProcessSql(pSql);
    }
  }
}