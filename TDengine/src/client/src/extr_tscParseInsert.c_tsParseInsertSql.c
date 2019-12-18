#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_13__ {scalar_t__ type; int n; char* z; } ;
struct TYPE_10__ {int /*<<< orphan*/  order; } ;
struct TYPE_12__ {int /*<<< orphan*/  payload; TYPE_2__ order; } ;
struct TYPE_11__ {TYPE_4__ cmd; TYPE_1__* pTscObj; } ;
struct TYPE_9__ {int /*<<< orphan*/  writeAuth; } ;
typedef  TYPE_3__ SSqlObj ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SSQLToken ;

/* Variables and functions */
 scalar_t__ TK_IMPORT ; 
 scalar_t__ TK_INSERT ; 
 scalar_t__ TK_INTO ; 
 int TSDB_CODE_INVALID_SQL ; 
 int TSDB_CODE_NO_RIGHTS ; 
 int /*<<< orphan*/  TSQL_SO_ASC ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ tStrGetToken (char*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tsParseInsertStatement (TYPE_3__*,char*,char*,char*) ; 

int tsParseInsertSql(SSqlObj *pSql, char *sql, char *acct, char *db) {
  if (!pSql->pTscObj->writeAuth) {
    return TSDB_CODE_NO_RIGHTS;
  }

  int32_t   index = 0;
  SSqlCmd *pCmd = &pSql->cmd;

  SSQLToken sToken = tStrGetToken(sql, &index, false, 0, NULL);
  if (sToken.type == TK_IMPORT) {
      pCmd->order.order = TSQL_SO_ASC;
  } else if (sToken.type != TK_INSERT) {
    if (sToken.n) {
      sToken.z[sToken.n] = 0;
      sprintf(pCmd->payload, "invalid keyword:%s", sToken.z);
    } else {
      strcpy(pCmd->payload, "no any keywords");
    }
    return TSDB_CODE_INVALID_SQL;
  }

  sToken = tStrGetToken(sql, &index, false, 0, NULL);
  if (sToken.type != TK_INTO) {
    strcpy(pCmd->payload, "keyword INTO is expected");
    return TSDB_CODE_INVALID_SQL;
  }

  return tsParseInsertStatement(pSql, sql + index, acct, db);
}