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
struct TYPE_10__ {int code; } ;
struct TYPE_11__ {void* sqlstr; TYPE_2__ res; } ;
struct TYPE_9__ {TYPE_3__* pSql; struct TYPE_9__* signature; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_DISCONNECTED ; 
 int TSDB_CODE_INVALID_SQL ; 
 size_t TSDB_MAX_SQL_LEN ; 
 int globalCode ; 
 void* realloc (void*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strtolower (void*,char const*) ; 
 int /*<<< orphan*/  taos_errstr (int /*<<< orphan*/ *) ; 
 int taos_query_imp (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

int taos_query(TAOS *taos, const char *sqlstr) {
  STscObj *pObj = (STscObj *)taos;
  if (pObj == NULL || pObj->signature != pObj) {
    globalCode = TSDB_CODE_DISCONNECTED;
    return TSDB_CODE_DISCONNECTED;
  }

  SSqlObj *pSql = pObj->pSql;
  SSqlRes *pRes = &pSql->res;

  size_t sqlLen = strlen(sqlstr);
  if (sqlLen > TSDB_MAX_SQL_LEN) {
    tscError("%p sql too long", pSql);
    pRes->code = TSDB_CODE_INVALID_SQL;
    return pRes->code;
  }

  void *sql = realloc(pSql->sqlstr, sqlLen + 1);
  if (sql == NULL) {
    pRes->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
    tscError("%p failed to malloc sql string buffer", pSql);
    tscTrace("%p SQL result:%d, %s pObj:%p", pSql, pRes->code, taos_errstr(taos), pObj);
    return pRes->code;
  }

  pSql->sqlstr = sql;
  strtolower(pSql->sqlstr, sqlstr);
  return taos_query_imp(pObj, pSql);
}