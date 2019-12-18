#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_11__ {int type; int numOfCols; int /*<<< orphan*/  meterId; TYPE_1__* schema; } ;
struct TYPE_10__ {int /*<<< orphan*/  thandle; TYPE_2__* pUser; scalar_t__ pDb; int /*<<< orphan*/  writeAuth; } ;
struct TYPE_9__ {int /*<<< orphan*/  user; } ;
struct TYPE_8__ {int bytes; } ;
typedef  TYPE_3__ SConnObj ;
typedef  TYPE_4__ SAlterTableMsg ;

/* Variables and functions */
 int TSDB_CODE_APP_ERROR ; 
 int TSDB_CODE_DB_NOT_SELECTED ; 
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_ALTER_TABLE_RSP ; 
 void* htons (int) ; 
 int /*<<< orphan*/  mError (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mLPrint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mgmtAlterMeter (scalar_t__,TYPE_4__*) ; 
 scalar_t__ mgmtCheckRedirectMsg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosSendSimpleRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mgmtProcessAlterTableMsg(char *pMsg, int msgLen, SConnObj *pConn) {
  SAlterTableMsg *pAlter = (SAlterTableMsg *)pMsg;
  int             code;

  if (mgmtCheckRedirectMsg(pConn, TSDB_MSG_TYPE_ALTER_TABLE_RSP) != 0) {
    return 0;
  }

  if (!pConn->writeAuth) {
    code = TSDB_CODE_NO_RIGHTS;
  } else {
    pAlter->type = htons(pAlter->type);
    pAlter->numOfCols = htons(pAlter->numOfCols);

    if (pAlter->numOfCols > 2) {
      mError("meter:%s error numOfCols:%d in alter table", pAlter->meterId, pAlter->numOfCols);
      code = TSDB_CODE_APP_ERROR;
    } else {
      if (pConn->pDb) {
        for (int32_t i = 0; i < pAlter->numOfCols; ++i) {
          pAlter->schema[i].bytes = htons(pAlter->schema[i].bytes);
        }

        code = mgmtAlterMeter(pConn->pDb, pAlter);
        if (code == 0) {
          mLPrint("meter:%s is altered by %s", pAlter->meterId, pConn->pUser->user);
        }
      } else {
        code = TSDB_CODE_DB_NOT_SELECTED;
      }
    }
  }

  taosSendSimpleRsp(pConn->thandle, TSDB_MSG_TYPE_ALTER_TABLE_RSP, code);

  return 0;
}