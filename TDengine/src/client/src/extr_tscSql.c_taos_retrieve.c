#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ command; } ;
struct TYPE_6__ {scalar_t__ qhandle; int numOfRows; } ;
struct TYPE_7__ {struct TYPE_7__* signature; TYPE_1__ res; TYPE_3__ cmd; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_SQL_FETCH ; 
 scalar_t__ TSDB_SQL_LOCAL ; 
 scalar_t__ TSDB_SQL_MGMT ; 
 scalar_t__ TSDB_SQL_RETRIEVE ; 
 int /*<<< orphan*/  tscProcessSql (TYPE_2__*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 

int taos_retrieve(TAOS_RES *res) {
  if (res == NULL) return 0;
  SSqlObj *pSql = (SSqlObj *)res;
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;
  if (pSql == NULL || pSql->signature != pSql) return 0;
  if (pRes->qhandle == 0) return 0;

  tscResetForNextRetrieve(pRes);

  if (pCmd->command < TSDB_SQL_LOCAL) {
    pCmd->command = (pCmd->command > TSDB_SQL_MGMT) ? TSDB_SQL_RETRIEVE : TSDB_SQL_FETCH;
  }
  tscProcessSql(pSql);

  return pRes->numOfRows;
}