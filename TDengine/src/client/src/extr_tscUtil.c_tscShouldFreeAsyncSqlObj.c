#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_12__ {scalar_t__ nSize; } ;
struct TYPE_11__ {size_t command; scalar_t__ vnodeIdx; TYPE_5__* pDataBlocks; } ;
struct TYPE_8__ {scalar_t__ code; } ;
struct TYPE_10__ {TYPE_1__ res; TYPE_4__ cmd; int /*<<< orphan*/ * pStream; TYPE_2__* pTscObj; int /*<<< orphan*/ * fp; struct TYPE_10__* signature; } ;
struct TYPE_9__ {TYPE_3__* pSql; TYPE_3__* pHb; } ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SDataBlockList ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_ACTION_IN_PROGRESS ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 size_t TSDB_SQL_CONNECT ; 
 size_t TSDB_SQL_INSERT ; 
 scalar_t__* tscKeepConn ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*) ; 

bool tscShouldFreeAsyncSqlObj(SSqlObj* pSql) {
  if (pSql == NULL || pSql->signature != pSql || pSql->fp == NULL) {
    return false;
  }

  STscObj* pTscObj = pSql->pTscObj;
  if (pSql->pStream != NULL || pTscObj->pHb == pSql) {
    return false;
  }

  int32_t command = pSql->cmd.command;
  if (pTscObj->pSql == pSql) {
    /*
     * in case of taos_connect_a query, the object should all be released, even it is the
     * master sql object. Otherwise, the master sql should not be released
     */
    if (command == TSDB_SQL_CONNECT && pSql->res.code != TSDB_CODE_SUCCESS) {
      return true;
    }

    return false;
  }

  if (command == TSDB_SQL_INSERT) {
    SSqlCmd* pCmd = &pSql->cmd;

    /*
     * in case of multi-vnode insertion, the object should not be released until all
     * data blocks have been submit to vnode.
     */
    SDataBlockList* pDataBlocks = pCmd->pDataBlocks;
    if (pDataBlocks == NULL || pCmd->vnodeIdx >= pDataBlocks->nSize) {
      tscTrace("%p object should be release since all data blocks have been submit", pSql);
      return true;
    } else {
      return false;
    }
  } else {
    return tscKeepConn[command] == 0 ||
           (pSql->res.code != TSDB_CODE_ACTION_IN_PROGRESS && pSql->res.code != TSDB_CODE_SUCCESS);
  }
}