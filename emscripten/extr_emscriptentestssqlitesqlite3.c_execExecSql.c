#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int execSql (int /*<<< orphan*/ *,char**,char*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int vacuumFinalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static int execExecSql(sqlite3 *db, char **pzErrMsg, const char *zSql){
  sqlite3_stmt *pStmt;
  int rc;

  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  if( rc!=SQLITE_OK ) return rc;

  while( SQLITE_ROW==sqlite3_step(pStmt) ){
    rc = execSql(db, pzErrMsg, (char*)sqlite3_column_text(pStmt, 0));
    if( rc!=SQLITE_OK ){
      vacuumFinalize(db, pStmt, pzErrMsg);
      return rc;
    }
  }

  return vacuumFinalize(db, pStmt, pzErrMsg);
}