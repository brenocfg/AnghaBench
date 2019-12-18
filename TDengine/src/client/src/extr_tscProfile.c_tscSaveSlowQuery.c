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
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ const useconds; } ;
struct TYPE_8__ {char* sqlstr; TYPE_2__* pTscObj; TYPE_1__ res; int /*<<< orphan*/  stime; } ;
struct TYPE_7__ {char* user; } ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int TSDB_SHOW_SQL_LEN ; 
 char* malloc (int) ; 
 int snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  taosTmrStart (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 char* tsMonitorDbName ; 
 int /*<<< orphan*/  tscSaveSlowQueryFp ; 
 int /*<<< orphan*/  tscTmr ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_3__*,scalar_t__ const,char*) ; 

void tscSaveSlowQuery(SSqlObj *pSql) {
  const static int64_t SLOW_QUERY_INTERVAL = 3000000L;
  if (pSql->res.useconds < SLOW_QUERY_INTERVAL) return;

  tscTrace("%p query time:%lld sql:%s", pSql, pSql->res.useconds, pSql->sqlstr);

  char *sql = malloc(200);
  int   len = snprintf(sql, 200, "insert into %s.slowquery values(now, '%s', %lld, %lld, '", tsMonitorDbName,
          pSql->pTscObj->user, pSql->stime, pSql->res.useconds);
  int sqlLen = snprintf(sql + len, TSDB_SHOW_SQL_LEN, "%s", pSql->sqlstr);
  if (sqlLen > TSDB_SHOW_SQL_LEN - 1) {
    sqlLen = len + TSDB_SHOW_SQL_LEN - 1;
  } else {
    sqlLen += len;
  }
  strcpy(sql + sqlLen, "')");

  taosTmrStart(tscSaveSlowQueryFp, 200, sql, tscTmr);
}