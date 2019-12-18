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
typedef  int uint8_t ;
typedef  scalar_t__ const int32_t ;
struct TYPE_10__ {int code; scalar_t__ qhandle; scalar_t__ numOfTotal; } ;
struct TYPE_11__ {int /*<<< orphan*/ * thandle; int /*<<< orphan*/ * fp; TYPE_2__ res; } ;
struct TYPE_9__ {TYPE_3__* pSql; struct TYPE_9__* signature; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_DISCONNECTED ; 
 int TSDB_CODE_INVALID_SQL ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* calloc (int,scalar_t__ const) ; 
 int /*<<< orphan*/  free (char*) ; 
 int globalCode ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strtolower (char*,char const*) ; 
 int /*<<< orphan*/  taos_errstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscDoQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_3__*,...) ; 
 int /*<<< orphan*/  tscFreeSqlObjPartial (TYPE_3__*) ; 
 scalar_t__ tscParseTblNameList (TYPE_3__*,char*,scalar_t__ const) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,...) ; 

int taos_load_table_info(TAOS *taos, const char *tableNameList) {
  const int32_t MAX_TABLE_NAME_LENGTH = 12*1024*1024; // 12MB list

  STscObj *pObj = (STscObj *)taos;
  if (pObj == NULL || pObj->signature != pObj) {
    globalCode = TSDB_CODE_DISCONNECTED;
    return TSDB_CODE_DISCONNECTED;
  }

  SSqlObj *pSql = pObj->pSql;
  SSqlRes *pRes = &pSql->res;

  pRes->numOfTotal = 0;  // the number of getting table meta from server
  pRes->code = 0;

  assert(pSql->fp == NULL);
  tscTrace("%p tableNameList: %s pObj:%p", pSql, tableNameList, pObj);

  int32_t tblListLen = strlen(tableNameList);
  if (tblListLen > MAX_TABLE_NAME_LENGTH) {
    tscError("%p tableNameList too long, length:%d, maximum allowed:%d", pSql, tblListLen, MAX_TABLE_NAME_LENGTH);
    pRes->code = TSDB_CODE_INVALID_SQL;
    return pRes->code;
  }

  char* str = calloc(1, tblListLen + 1);
  if (str == NULL) {
    pRes->code = TSDB_CODE_CLI_OUT_OF_MEMORY;
    tscError("%p failed to malloc sql string buffer", pSql);
    return pRes->code;
  }

  strtolower(str, tableNameList);
  pRes->code = (uint8_t) tscParseTblNameList(pSql, str, tblListLen);

  /*
   * set the qhandle to 0 before return in order to erase the qhandle value assigned in the previous successful query.
   * If qhandle is NOT set 0, the function of taos_free_result() will send message to server by calling tscProcessSql()
   * to free connection, which may cause segment fault, when the parse phrase is not even successfully executed.
   */
  pRes->qhandle = 0;
  pSql->thandle = NULL;
  free(str);

  if (pRes->code != TSDB_CODE_SUCCESS) {
    return pRes->code;
  }

  tscDoQuery(pSql);

  tscTrace("%p load multi metermeta result:%d %s pObj:%p", pSql, pRes->code, taos_errstr(taos), pObj);
  if (pRes->code != TSDB_CODE_SUCCESS) {
    tscFreeSqlObjPartial(pSql);
  }

  return pRes->code;
}