#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct SSqlInfo {int sqlType; TYPE_1__* pDCLInfo; } ;
typedef  int int8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
struct TYPE_15__ {scalar_t__ payloadLen; int /*<<< orphan*/  payload; int /*<<< orphan*/  showType; int /*<<< orphan*/  command; } ;
struct TYPE_14__ {TYPE_3__ cmd; } ;
struct TYPE_13__ {int nTokens; TYPE_4__* a; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;
typedef  TYPE_4__ SSQLToken ;
typedef  TYPE_5__ SMeterMetaInfo ;

/* Variables and functions */
#define  SHOW_ACCOUNTS 142 
#define  SHOW_CONFIGS 141 
#define  SHOW_CONNECTIONS 140 
#define  SHOW_DATABASES 139 
#define  SHOW_DNODES 138 
#define  SHOW_GRANTS 137 
#define  SHOW_MNODES 136 
#define  SHOW_MODULES 135 
#define  SHOW_QUERIES 134 
#define  SHOW_SCORES 133 
#define  SHOW_STABLES 132 
#define  SHOW_STREAMS 131 
#define  SHOW_TABLES 130 
#define  SHOW_USERS 129 
#define  SHOW_VGROUPS 128 
 scalar_t__ TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DB_NAME_LEN ; 
 scalar_t__ TSDB_METER_NAME_LEN ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_ACCT ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_CONFIGS ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_CONNS ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_DB ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_GRANTS ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_METRIC ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_MNODE ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_MODULE ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_PNODE ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_QUERIES ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_SCORES ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_STREAMS ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_TABLE ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_USER ; 
 int /*<<< orphan*/  TSDB_MGMT_TABLE_VGROUP ; 
 int /*<<< orphan*/  TSDB_SQL_SHOW ; 
 int /*<<< orphan*/  getAccountId (TYPE_2__*) ; 
 int /*<<< orphan*/  setErrMsg (TYPE_3__*,char const*) ; 
 scalar_t__ setObjFullName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strdequote (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* tscGetMeterMetaInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tscValidateName (TYPE_4__*) ; 

int32_t setShowInfo(SSqlObj* pSql, struct SSqlInfo* pInfo) {
  SSqlCmd*        pCmd = &pSql->cmd;
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);

  pCmd->command = TSDB_SQL_SHOW;
  int8_t type = pInfo->sqlType;

  const char* msg = "database name too long";
  const char* msg1 = "invalid database name";
  const char* msg2 = "pattern filter string too long";

  switch (type) {
    case SHOW_VGROUPS:
      pCmd->showType = TSDB_MGMT_TABLE_VGROUP;
      break;
    case SHOW_TABLES:
      pCmd->showType = TSDB_MGMT_TABLE_TABLE;
      break;
    case SHOW_STABLES:
      pCmd->showType = TSDB_MGMT_TABLE_METRIC;
      break;

    case SHOW_DATABASES:
      pCmd->showType = TSDB_MGMT_TABLE_DB;
      break;
    case SHOW_MNODES:
      pCmd->showType = TSDB_MGMT_TABLE_MNODE;
      break;
    case SHOW_DNODES:
      pCmd->showType = TSDB_MGMT_TABLE_PNODE;
      break;
    case SHOW_ACCOUNTS:
      pCmd->showType = TSDB_MGMT_TABLE_ACCT;
      break;
    case SHOW_USERS:
      pCmd->showType = TSDB_MGMT_TABLE_USER;
      break;
    case SHOW_MODULES:
      pCmd->showType = TSDB_MGMT_TABLE_MODULE;
      break;
    case SHOW_CONNECTIONS:
      pCmd->showType = TSDB_MGMT_TABLE_CONNS;
      break;
    case SHOW_QUERIES:
      pCmd->showType = TSDB_MGMT_TABLE_QUERIES;
      break;
    case SHOW_SCORES:
      pCmd->showType = TSDB_MGMT_TABLE_SCORES;
      break;
    case SHOW_GRANTS:
      pCmd->showType = TSDB_MGMT_TABLE_GRANTS;
      break;
    case SHOW_STREAMS:
      pCmd->showType = TSDB_MGMT_TABLE_STREAMS;
      break;
    case SHOW_CONFIGS:
      pCmd->showType = TSDB_MGMT_TABLE_CONFIGS;
      break;
    default:
      return TSDB_CODE_INVALID_SQL;
  }

  /*
   * database prefix in pInfo->pDCLInfo->a[0]
   * wildcard in like clause in pInfo->pDCLInfo->a[1]
   */
  if (type == SHOW_TABLES || type == SHOW_STABLES || type == SHOW_VGROUPS) {
    // db prefix in tagCond, show table conds in payload
    if (pInfo->pDCLInfo->nTokens > 0) {
      SSQLToken* pDbPrefixToken = &pInfo->pDCLInfo->a[0];

      if (pDbPrefixToken->n > TSDB_DB_NAME_LEN) {  // db name is too long
        setErrMsg(pCmd, msg);
        return TSDB_CODE_INVALID_SQL;
      }

      if (pDbPrefixToken->n > 0 && tscValidateName(pDbPrefixToken) != TSDB_CODE_SUCCESS) {
        setErrMsg(pCmd, msg1);
        return TSDB_CODE_INVALID_SQL;
      }

      int32_t ret = 0;
      if (pDbPrefixToken->n > 0) {  // has db prefix
        ret = setObjFullName(pMeterMetaInfo->name, getAccountId(pSql), pDbPrefixToken, NULL, NULL);
      }

      if (ret != TSDB_CODE_SUCCESS) {
        return ret;
      }

      if (type != SHOW_VGROUPS && pInfo->pDCLInfo->nTokens == 2) {
        // set the like conds for show tables
        SSQLToken* likeToken = &pInfo->pDCLInfo->a[1];

        strncpy(pCmd->payload, likeToken->z, likeToken->n);
        pCmd->payloadLen = strdequote(pCmd->payload);

        if (pCmd->payloadLen > TSDB_METER_NAME_LEN) {
          setErrMsg(pCmd, msg2);
          return TSDB_CODE_INVALID_SQL;  // wildcard is too long
        }
      }
    }
  }

  return TSDB_CODE_SUCCESS;
}