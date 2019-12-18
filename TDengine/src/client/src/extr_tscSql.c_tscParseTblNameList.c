#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_17__ {char* name; } ;
struct TYPE_16__ {size_t n; char* z; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {scalar_t__ count; char* payload; scalar_t__ allocSize; int payloadLen; int /*<<< orphan*/  command; } ;
struct TYPE_14__ {TYPE_2__ cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  TYPE_2__ SSqlCmd ;
typedef  TYPE_3__ SSQLToken ;
typedef  TYPE_4__ SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TK_ID ; 
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_INVALID_METER_ID ; 
 int TSDB_CODE_SUCCESS ; 
 int TSDB_METER_ID_LEN ; 
 scalar_t__ TSDB_MULTI_METERMETA_MAX_NUM ; 
 int /*<<< orphan*/  TSDB_SQL_MULTI_META ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* realloc (char*,size_t) ; 
 int setMeterID (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strtrim (char*) ; 
 int /*<<< orphan*/  tSQLGetToken (char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* tscAddEmptyMeterMetaInfo (TYPE_2__*) ; 
 int tscAllocPayload (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  tscCleanSqlCmd (TYPE_2__*) ; 
 int /*<<< orphan*/  tscRemoveAllMeterMetaInfo (TYPE_2__*,int) ; 
 int tscValidateName (TYPE_3__*) ; 

__attribute__((used)) static int tscParseTblNameList(SSqlObj *pSql, const char* tblNameList, int32_t tblListLen) {
  // must before clean the sqlcmd object
  tscRemoveAllMeterMetaInfo(&pSql->cmd, false);
  tscCleanSqlCmd(&pSql->cmd);

  SSqlCmd *pCmd = &pSql->cmd;

  pCmd->command = TSDB_SQL_MULTI_META;
  pCmd->count = 0;

  int   code = TSDB_CODE_INVALID_METER_ID;
  char *str = (char*) tblNameList;

  SMeterMetaInfo *pMeterMetaInfo = tscAddEmptyMeterMetaInfo(pCmd);

  if ((code = tscAllocPayload(pCmd, tblListLen+16)) != TSDB_CODE_SUCCESS) {
    return code;
  }

  char *nextStr;
  char  tblName[TSDB_METER_ID_LEN];
  int   payloadLen = 0;
  char *pMsg = pCmd->payload;
  while (1) {
    nextStr = strchr(str, ',');
    if (nextStr == NULL) {
      break;
    }

    memcpy(tblName, str, nextStr - str);
    int32_t len = nextStr - str;
    tblName[len] = '\0';

    str = nextStr + 1;

    strtrim(tblName);
    len = (uint32_t)strlen(tblName);
    
    SSQLToken sToken = {.n = len, .type = TK_ID, .z = tblName};
    tSQLGetToken(tblName, &sToken.type);

    // Check if the table name available or not
    if (tscValidateName(&sToken) != TSDB_CODE_SUCCESS) {
      code = TSDB_CODE_INVALID_METER_ID;
      sprintf(pCmd->payload, "table name is invalid");
      return code;
    }

    if ((code = setMeterID(pSql, &sToken, 0)) != TSDB_CODE_SUCCESS) {
      return code;
    }

    if (++pCmd->count > TSDB_MULTI_METERMETA_MAX_NUM) {
      code = TSDB_CODE_INVALID_METER_ID;
      sprintf(pCmd->payload, "tables over the max number");
      return code;
    }

    if (payloadLen + strlen(pMeterMetaInfo->name) + 128 >= pCmd->allocSize) {
      char *pNewMem = realloc(pCmd->payload, pCmd->allocSize + tblListLen);
      if (pNewMem == NULL) {
        code = TSDB_CODE_CLI_OUT_OF_MEMORY;
        sprintf(pCmd->payload, "failed to allocate memory");
        return code;
      }

      pCmd->payload = pNewMem;
      pCmd->allocSize = pCmd->allocSize + tblListLen;
      pMsg = pCmd->payload;
    }

    payloadLen += sprintf(pMsg + payloadLen, "%s,", pMeterMetaInfo->name);
  }

  *(pMsg + payloadLen) = '\0';
  pCmd->payloadLen = payloadLen + 1;

  return TSDB_CODE_SUCCESS;
}