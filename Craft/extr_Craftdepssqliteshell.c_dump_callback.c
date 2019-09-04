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
struct callback_data {int writableSchema; int /*<<< orphan*/  db; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int SQLITE_CORRUPT ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (char**) ; 
 char* appendText (char*,char const*,char) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int run_table_dump_query (struct callback_data*,char*,char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*,char const*) ; 
 int sqlite3_prepare (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int dump_callback(void *pArg, int nArg, char **azArg, char **azCol){
  int rc;
  const char *zTable;
  const char *zType;
  const char *zSql;
  const char *zPrepStmt = 0;
  struct callback_data *p = (struct callback_data *)pArg;

  UNUSED_PARAMETER(azCol);
  if( nArg!=3 ) return 1;
  zTable = azArg[0];
  zType = azArg[1];
  zSql = azArg[2];
  
  if( strcmp(zTable, "sqlite_sequence")==0 ){
    zPrepStmt = "DELETE FROM sqlite_sequence;\n";
  }else if( strcmp(zTable, "sqlite_stat1")==0 ){
    fprintf(p->out, "ANALYZE sqlite_master;\n");
  }else if( strncmp(zTable, "sqlite_", 7)==0 ){
    return 0;
  }else if( strncmp(zSql, "CREATE VIRTUAL TABLE", 20)==0 ){
    char *zIns;
    if( !p->writableSchema ){
      fprintf(p->out, "PRAGMA writable_schema=ON;\n");
      p->writableSchema = 1;
    }
    zIns = sqlite3_mprintf(
       "INSERT INTO sqlite_master(type,name,tbl_name,rootpage,sql)"
       "VALUES('table','%q','%q',0,'%q');",
       zTable, zTable, zSql);
    fprintf(p->out, "%s\n", zIns);
    sqlite3_free(zIns);
    return 0;
  }else{
    fprintf(p->out, "%s;\n", zSql);
  }

  if( strcmp(zType, "table")==0 ){
    sqlite3_stmt *pTableInfo = 0;
    char *zSelect = 0;
    char *zTableInfo = 0;
    char *zTmp = 0;
    int nRow = 0;
   
    zTableInfo = appendText(zTableInfo, "PRAGMA table_info(", 0);
    zTableInfo = appendText(zTableInfo, zTable, '"');
    zTableInfo = appendText(zTableInfo, ");", 0);

    rc = sqlite3_prepare(p->db, zTableInfo, -1, &pTableInfo, 0);
    free(zTableInfo);
    if( rc!=SQLITE_OK || !pTableInfo ){
      return 1;
    }

    zSelect = appendText(zSelect, "SELECT 'INSERT INTO ' || ", 0);
    /* Always quote the table name, even if it appears to be pure ascii,
    ** in case it is a keyword. Ex:  INSERT INTO "table" ... */
    zTmp = appendText(zTmp, zTable, '"');
    if( zTmp ){
      zSelect = appendText(zSelect, zTmp, '\'');
      free(zTmp);
    }
    zSelect = appendText(zSelect, " || ' VALUES(' || ", 0);
    rc = sqlite3_step(pTableInfo);
    while( rc==SQLITE_ROW ){
      const char *zText = (const char *)sqlite3_column_text(pTableInfo, 1);
      zSelect = appendText(zSelect, "quote(", 0);
      zSelect = appendText(zSelect, zText, '"');
      rc = sqlite3_step(pTableInfo);
      if( rc==SQLITE_ROW ){
        zSelect = appendText(zSelect, "), ", 0);
      }else{
        zSelect = appendText(zSelect, ") ", 0);
      }
      nRow++;
    }
    rc = sqlite3_finalize(pTableInfo);
    if( rc!=SQLITE_OK || nRow==0 ){
      free(zSelect);
      return 1;
    }
    zSelect = appendText(zSelect, "|| ')' FROM  ", 0);
    zSelect = appendText(zSelect, zTable, '"');

    rc = run_table_dump_query(p, zSelect, zPrepStmt);
    if( rc==SQLITE_CORRUPT ){
      zSelect = appendText(zSelect, " ORDER BY rowid DESC", 0);
      run_table_dump_query(p, zSelect, 0);
    }
    free(zSelect);
  }
  return 0;
}