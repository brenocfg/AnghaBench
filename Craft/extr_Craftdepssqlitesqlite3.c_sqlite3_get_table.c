#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int errCode; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_7__ {char* zErrMsg; int nRow; int nColumn; int nData; int nAlloc; int rc; char** azResult; } ;
typedef  TYPE_2__ TabResult ;

/* Variables and functions */
 int SQLITE_ABORT ; 
 char* SQLITE_INT_TO_PTR (int) ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_exec (TYPE_1__*,char const*,int /*<<< orphan*/ ,TYPE_2__*,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_free_table (char**) ; 
 int /*<<< orphan*/  sqlite3_get_table_cb ; 
 char** sqlite3_malloc (int) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 char** sqlite3_realloc (char**,int) ; 

int sqlite3_get_table(
  sqlite3 *db,                /* The database on which the SQL executes */
  const char *zSql,           /* The SQL to be executed */
  char ***pazResult,          /* Write the result table here */
  int *pnRow,                 /* Write the number of rows in the result here */
  int *pnColumn,              /* Write the number of columns of result here */
  char **pzErrMsg             /* Write error messages here */
){
  int rc;
  TabResult res;

  *pazResult = 0;
  if( pnColumn ) *pnColumn = 0;
  if( pnRow ) *pnRow = 0;
  if( pzErrMsg ) *pzErrMsg = 0;
  res.zErrMsg = 0;
  res.nRow = 0;
  res.nColumn = 0;
  res.nData = 1;
  res.nAlloc = 20;
  res.rc = SQLITE_OK;
  res.azResult = sqlite3_malloc(sizeof(char*)*res.nAlloc );
  if( res.azResult==0 ){
     db->errCode = SQLITE_NOMEM;
     return SQLITE_NOMEM;
  }
  res.azResult[0] = 0;
  rc = sqlite3_exec(db, zSql, sqlite3_get_table_cb, &res, pzErrMsg);
  assert( sizeof(res.azResult[0])>= sizeof(res.nData) );
  res.azResult[0] = SQLITE_INT_TO_PTR(res.nData);
  if( (rc&0xff)==SQLITE_ABORT ){
    sqlite3_free_table(&res.azResult[1]);
    if( res.zErrMsg ){
      if( pzErrMsg ){
        sqlite3_free(*pzErrMsg);
        *pzErrMsg = sqlite3_mprintf("%s",res.zErrMsg);
      }
      sqlite3_free(res.zErrMsg);
    }
    db->errCode = res.rc;  /* Assume 32-bit assignment is atomic */
    return res.rc;
  }
  sqlite3_free(res.zErrMsg);
  if( rc!=SQLITE_OK ){
    sqlite3_free_table(&res.azResult[1]);
    return rc;
  }
  if( res.nAlloc>res.nData ){
    char **azNew;
    azNew = sqlite3_realloc( res.azResult, sizeof(char*)*res.nData );
    if( azNew==0 ){
      sqlite3_free_table(&res.azResult[1]);
      db->errCode = SQLITE_NOMEM;
      return SQLITE_NOMEM;
    }
    res.azResult = azNew;
  }
  *pazResult = &res.azResult[1];
  if( pnColumn ) *pnColumn = res.nColumn;
  if( pnRow ) *pnRow = res.nRow;
  return rc;
}