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
struct TYPE_11__ {scalar_t__ command; } ;
struct TYPE_9__ {scalar_t__ qhandle; scalar_t__ code; scalar_t__ row; scalar_t__ numOfRows; int /*<<< orphan*/  numOfTotal; } ;
struct TYPE_10__ {TYPE_1__ res; TYPE_3__ cmd; } ;
typedef  int /*<<< orphan*/ * TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_METRIC_JOIN_RETRIEVE ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 scalar_t__ TSDB_SQL_RETRIEVE_EMPTY_RESULT ; 
 scalar_t__ TSDB_SQL_RETRIEVE_METRIC ; 
 int /*<<< orphan*/ * getOneRowFromBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  tscFetchDatablockFromSubquery (TYPE_2__*) ; 
 int /*<<< orphan*/ * tscJoinResultsetFromBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_2__*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 

TAOS_ROW taos_fetch_row_impl(TAOS_RES *res) {
  SSqlObj *pSql = (SSqlObj *)res;
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  if (pRes->qhandle == 0 || pCmd->command == TSDB_SQL_RETRIEVE_EMPTY_RESULT) {
    return NULL;
  }

  if (pCmd->command == TSDB_SQL_METRIC_JOIN_RETRIEVE) {
    tscFetchDatablockFromSubquery(pSql);
    if (pRes->code == TSDB_CODE_SUCCESS) {
      return tscJoinResultsetFromBuf(pSql);
    } else {
      return NULL;
    }

  } else if (pRes->row >= pRes->numOfRows) {
    tscResetForNextRetrieve(pRes);

    if (pCmd->command < TSDB_SQL_LOCAL) {
      pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;
    }

    tscProcessSql(pSql);
    if (pRes->numOfRows == 0) {
      return NULL;
    }

    // local reducer has handle this situation
    if (pCmd->command != TSDB_SQL_RETRIEVE_METRIC) {
      pRes->numOfTotal += pRes->numOfRows;
    }
  }

  return getOneRowFromBuf(pSql);
}