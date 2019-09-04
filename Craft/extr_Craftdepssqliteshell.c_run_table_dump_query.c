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
struct callback_data {int /*<<< orphan*/  nErr; int /*<<< orphan*/  db; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_table_dump_query(
  struct callback_data *p, /* Query context */
  const char *zSelect,     /* SELECT statement to extract content */
  const char *zFirstRow    /* Print before first row, if not NULL */
){
  sqlite3_stmt *pSelect;
  int rc;
  int nResult;
  int i;
  const char *z;
  rc = sqlite3_prepare(p->db, zSelect, -1, &pSelect, 0);
  if( rc!=SQLITE_OK || !pSelect ){
    fprintf(p->out, "/**** ERROR: (%d) %s *****/\n", rc, sqlite3_errmsg(p->db));
    p->nErr++;
    return rc;
  }
  rc = sqlite3_step(pSelect);
  nResult = sqlite3_column_count(pSelect);
  while( rc==SQLITE_ROW ){
    if( zFirstRow ){
      fprintf(p->out, "%s", zFirstRow);
      zFirstRow = 0;
    }
    z = (const char*)sqlite3_column_text(pSelect, 0);
    fprintf(p->out, "%s", z);
    for(i=1; i<nResult; i++){ 
      fprintf(p->out, ",%s", sqlite3_column_text(pSelect, i));
    }
    if( z==0 ) z = "";
    while( z[0] && (z[0]!='-' || z[1]!='-') ) z++;
    if( z[0] ){
      fprintf(p->out, "\n;\n");
    }else{
      fprintf(p->out, ";\n");
    }    
    rc = sqlite3_step(pSelect);
  }
  rc = sqlite3_finalize(pSelect);
  if( rc!=SQLITE_OK ){
    fprintf(p->out, "/**** ERROR: (%d) %s *****/\n", rc, sqlite3_errmsg(p->db));
    p->nErr++;
  }
  return rc;
}