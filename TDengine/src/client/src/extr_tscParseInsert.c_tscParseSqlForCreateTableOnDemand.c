#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_16__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_28__ {int /*<<< orphan*/  name; TYPE_16__* pMeterMeta; } ;
struct TYPE_27__ {scalar_t__ type; char* z; scalar_t__ n; } ;
struct TYPE_26__ {scalar_t__ type; scalar_t__ bytes; } ;
struct TYPE_25__ {scalar_t__ payload; } ;
struct TYPE_24__ {TYPE_3__ cmd; } ;
struct TYPE_23__ {char* data; int /*<<< orphan*/  name; } ;
struct TYPE_22__ {scalar_t__ numOfTags; int /*<<< orphan*/  precision; } ;
typedef  TYPE_1__ STagData ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SSchema ;
typedef  TYPE_5__ SSQLToken ;
typedef  TYPE_6__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TK_LP ; 
 scalar_t__ TK_RP ; 
 scalar_t__ TK_STRING ; 
 scalar_t__ TK_TAGS ; 
 scalar_t__ TK_USING ; 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 int /*<<< orphan*/  TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  UTIL_METER_IS_METRIC (TYPE_6__*) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setErrMsg (scalar_t__,char*) ; 
 scalar_t__ setMeterID (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ tStrGetToken (char*,scalar_t__*,int,int,int*) ; 
 TYPE_4__* tsGetTagSchema (TYPE_16__*) ; 
 scalar_t__ tsParseOneColumnData (TYPE_4__*,TYPE_5__*,char*,scalar_t__,char**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ tscGetMeterMeta (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tscGetMeterMetaEx (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tscValidateName (TYPE_5__*) ; 

__attribute__((used)) static int32_t tscParseSqlForCreateTableOnDemand(char **sqlstr, SSqlObj *pSql) {
  int32_t   index = 0;
  SSQLToken sToken;
  SSQLToken tableToken;
  int32_t   code = TSDB_CODE_SUCCESS;

  SSqlCmd *       pCmd = &pSql->cmd;
  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  char *sql = *sqlstr;
  // get the token of specified table
  index = 0;
  tableToken = tStrGetToken(sql, &index, false, 0, NULL);
  sql += index;

  char *cstart = NULL;
  char *cend = NULL;

  // skip possibly exists column list
  index = 0;
  sToken = tStrGetToken(sql, &index, false, 0, NULL);
  sql += index;

  int32_t numOfColList = 0;
  bool    createTable = false;

  if (sToken.type == TK_LP) {
    cstart = &sToken.z[0];
    index = 0;
    while (1) {
      sToken = tStrGetToken(sql, &index, false, 0, NULL);
      if (sToken.type == TK_RP) {
        cend = &sToken.z[0];
        break;
      }

      ++numOfColList;
    }

    sToken = tStrGetToken(sql, &index, false, 0, NULL);
    sql += index;
  }

  if (numOfColList == 0 && cstart != NULL) {
    return TSDB_CODE_INVALID_SQL;
  }

  if (sToken.type == TK_USING) {
    // create table if not exists
    index = 0;
    sToken = tStrGetToken(sql, &index, false, 0, NULL);
    sql += index;

    STagData *pTag = (STagData *)pCmd->payload;
    memset(pTag, 0, sizeof(STagData));
    setMeterID(pSql, &sToken, 0);

    strncpy(pTag->name, pMeterMetaInfo->name, TSDB_METER_ID_LEN);
    code = tscGetMeterMeta(pSql, pTag->name, 0);
    if (code != TSDB_CODE_SUCCESS) {
      return code;
    }

    if (!UTIL_METER_IS_METRIC(pMeterMetaInfo)) {
      strcpy(pCmd->payload, "create table only from super table is allowed");
      return TSDB_CODE_INVALID_SQL;
    }

    char *   tagVal = pTag->data;
    SSchema *pTagSchema = tsGetTagSchema(pMeterMetaInfo->pMeterMeta);

    index = 0;
    sToken = tStrGetToken(sql, &index, false, 0, NULL);
    sql += index;
    if (sToken.type != TK_TAGS) {
      setErrMsg(pCmd->payload, sql);
      return TSDB_CODE_INVALID_SQL;
    }

    int32_t  numOfTagValues = 0;
    uint32_t ignoreTokenTypes = TK_LP;
    uint32_t numOfIgnoreToken = 1;
    while (1) {
      index = 0;
      sToken = tStrGetToken(sql, &index, true, numOfIgnoreToken, &ignoreTokenTypes);
      sql += index;
      if (sToken.n == 0) {
        break;
      } else if (sToken.type == TK_RP) {
        break;
      }

      // Remove quotation marks
      if (TK_STRING == sToken.type) {
        sToken.z++;
        sToken.n -= 2;
      }

      code = tsParseOneColumnData(&pTagSchema[numOfTagValues], &sToken, tagVal, pCmd->payload, &sql, false,
                                  pMeterMetaInfo->pMeterMeta->precision);
      if (code != TSDB_CODE_SUCCESS) {
        setErrMsg(pCmd->payload, sql);
        return TSDB_CODE_INVALID_SQL;
      }

      if ((pTagSchema[numOfTagValues].type == TSDB_DATA_TYPE_BINARY ||
           pTagSchema[numOfTagValues].type == TSDB_DATA_TYPE_NCHAR) &&
          sToken.n > pTagSchema[numOfTagValues].bytes) {
        strcpy(pCmd->payload, "tag value too long");
        return TSDB_CODE_INVALID_SQL;
      }

      tagVal += pTagSchema[numOfTagValues++].bytes;
    }

    if (numOfTagValues != pMeterMetaInfo->pMeterMeta->numOfTags) {
      setErrMsg(pCmd->payload, sql);
      return TSDB_CODE_INVALID_SQL;
    }

    if (tscValidateName(&tableToken) != TSDB_CODE_SUCCESS) {
      setErrMsg(pCmd->payload, sql);
      return TSDB_CODE_INVALID_SQL;
    }

    int32_t ret = setMeterID(pSql, &tableToken, 0);
    if (ret != TSDB_CODE_SUCCESS) {
      return ret;
    }

    createTable = true;
    code = tscGetMeterMetaEx(pSql, pMeterMetaInfo->name, true);
  } else {
    if (cstart != NULL) {
      sql = cstart;
    } else {
      sql = sToken.z;
    }
    code = tscGetMeterMeta(pSql, pMeterMetaInfo->name, 0);
  }

  int32_t len = cend - cstart + 1;
  if (cstart != NULL && createTable == true) {
    /* move the column list to start position of the next accessed points */
    memmove(sql - len, cstart, len);
    *sqlstr = sql - len;
  } else {
    *sqlstr = sql;
  }

  return code;
}