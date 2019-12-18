#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {int order; } ;
struct TYPE_12__ {int numOfOutputCols; } ;
struct TYPE_16__ {scalar_t__ command; TYPE_10__ order; TYPE_1__ fieldsInfo; } ;
struct TYPE_14__ {scalar_t__ qhandle; int numOfRows; int numOfTotal; int* bytes; scalar_t__* tsrow; } ;
struct TYPE_15__ {TYPE_2__* pTscObj; TYPE_3__ res; TYPE_5__ cmd; } ;
struct TYPE_13__ {TYPE_4__* pSql; } ;
typedef  scalar_t__* TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlRes ;
typedef  TYPE_4__ SSqlObj ;
typedef  TYPE_5__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSC_GET_RESPTR_BASE (TYPE_3__*,TYPE_5__*,int,TYPE_10__) ; 
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 scalar_t__ TSDB_SQL_RETRIEVE_METRIC ; 
 scalar_t__ TSQL_SO_DESC ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_4__*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_3__*) ; 

int taos_fetch_block_impl(TAOS_RES *res, TAOS_ROW *rows) {
  SSqlObj *pSql = (SSqlObj *)res;
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;
  STscObj *pObj = pSql->pTscObj;

  if (pRes->qhandle == 0 || pObj->pSql != pSql) {
    *rows = NULL;
    return 0;
  }

  // Retrieve new block
  tscResetForNextRetrieve(pRes);
  if (pCmd->command < TSDB_SQL_LOCAL) {
    pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;
  }

  tscProcessSql(pSql);
  if (pRes->numOfRows == 0) {
    *rows = NULL;
    return 0;
  }

  // secondary merge has handle this situation
  if (pCmd->command != TSDB_SQL_RETRIEVE_METRIC) {
    pRes->numOfTotal += pRes->numOfRows;
  }

  for (int i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    pRes->tsrow[i] = TSC_GET_RESPTR_BASE(pRes, pCmd, i, pCmd->order) +
                     pRes->bytes[i] * (1 - pCmd->order.order) * (pRes->numOfRows - 1);
  }

  *rows = pRes->tsrow;

  return (pCmd->order.order == TSQL_SO_DESC) ? pRes->numOfRows : -pRes->numOfRows;
}