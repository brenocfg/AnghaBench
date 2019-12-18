#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_13__ {int numOfRows; scalar_t__ code; scalar_t__ qhandle; scalar_t__ numOfTotal; } ;
struct TYPE_14__ {int /*<<< orphan*/ * thandle; int /*<<< orphan*/  sqlstr; TYPE_2__ res; } ;
struct TYPE_12__ {int /*<<< orphan*/  db; int /*<<< orphan*/  acctId; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  taos_errstr (TYPE_1__*) ; 
 scalar_t__ tsParseSql (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tscDoQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  tscFreeSqlObjPartial (TYPE_3__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,int,TYPE_1__*,...) ; 

int taos_query_imp(STscObj* pObj, SSqlObj* pSql) {
  SSqlRes *pRes = &pSql->res;

  pRes->numOfRows = 1;
  pRes->numOfTotal = 0;
  tscTrace("%p SQL: %s pObj:%p", pSql, pSql->sqlstr, pObj);

  pRes->code = (uint8_t)tsParseSql(pSql, pObj->acctId, pObj->db, false);

  /*
   * set the qhandle to 0 before return in order to erase the qhandle value assigned in the previous successful query.
   * If qhandle is NOT set 0, the function of taos_free_result() will send message to server by calling tscProcessSql()
   * to free connection, which may cause segment fault, when the parse phrase is not even successfully executed.
   */
  pRes->qhandle = 0;
  pSql->thandle = NULL;

  if (pRes->code != TSDB_CODE_SUCCESS) return pRes->code;

  tscDoQuery(pSql);

  tscTrace("%p SQL result:%d, %s pObj:%p", pSql, pRes->code, taos_errstr(pObj), pObj);
  if (pRes->code != TSDB_CODE_SUCCESS) {
    tscFreeSqlObjPartial(pSql);
  }

  return pRes->code;
}