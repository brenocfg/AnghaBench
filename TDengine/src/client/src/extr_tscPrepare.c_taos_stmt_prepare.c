#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int isInsert; TYPE_1__* pSql; } ;
struct TYPE_5__ {char* sqlstr; } ;
typedef  int /*<<< orphan*/  TAOS_STMT ;
typedef  TYPE_2__ STscStmt ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int insertStmtPrepare (TYPE_2__*) ; 
 scalar_t__ malloc (unsigned long) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned long) ; 
 int normalStmtPrepare (TYPE_2__*) ; 
 unsigned long strlen (char const*) ; 
 int /*<<< orphan*/  strtolower (char*,char*) ; 
 int /*<<< orphan*/  tscError (char*) ; 
 scalar_t__ tscIsInsertOrImportData (char*) ; 

int taos_stmt_prepare(TAOS_STMT* stmt, const char* sql, unsigned long length) {
  STscStmt* pStmt = (STscStmt*)stmt;
  if (length == 0) {
    length = strlen(sql);
  }
  char* sqlstr = (char*)malloc(length + 1);
  if (sqlstr == NULL) {
    tscError("failed to malloc sql string buffer");
    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  }
  memcpy(sqlstr, sql, length);
  sqlstr[length] = 0;
  strtolower(sqlstr, sqlstr);

  pStmt->pSql->sqlstr = sqlstr;
  if (tscIsInsertOrImportData(sqlstr)) {
    pStmt->isInsert = true;
    return insertStmtPrepare(pStmt);
  }

  pStmt->isInsert = false;
  return normalStmtPrepare(pStmt);
}