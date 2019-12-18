#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_2__ SSQLToken ;
typedef  TYPE_3__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/ * getAccountId (TYPE_1__*) ; 
 int /*<<< orphan*/  getCurrentDBName (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ hasSpecifyDB (TYPE_2__*) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ setObjFullName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* tscGetMeterMetaInfo (int /*<<< orphan*/ *,scalar_t__) ; 

int32_t setMeterID(SSqlObj* pSql, SSQLToken* pzTableName, int32_t tableIndex) {
  const char* msg = "name too long";

  SSqlCmd*        pCmd = &pSql->cmd;
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, tableIndex);
  int32_t         code = TSDB_CODE_SUCCESS;

  if (hasSpecifyDB(pzTableName)) {
    /*
     * db has been specified in sql string
     * so we ignore current db path
     */
    code = setObjFullName(pMeterMetaInfo->name, getAccountId(pSql), NULL, pzTableName, NULL);
  } else {  // get current DB name first, then set it into path
    SSQLToken t = {0};
    getCurrentDBName(pSql, &t);

    code = setObjFullName(pMeterMetaInfo->name, NULL, &t, pzTableName, NULL);
  }

  if (code != TSDB_CODE_SUCCESS) {
    setErrMsg(pCmd, msg);
  }

  return code;
}