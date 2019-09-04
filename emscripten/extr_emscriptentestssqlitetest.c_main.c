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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  callback ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 

int main(){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  int i;
  const char *commands[] = {
    "CREATE TABLE t1(a INTEGER, b INTEGER, c VARCHAR(100));",
    "INSERT INTO t1 VALUES(1,13153,'thirteen thousand one hundred fifty three');",
    "INSERT INTO t1 VALUES(1,987,'some other number');",
    "SELECT count(*) FROM t1;",
    "SELECT a, b, c FROM t1;",
    NULL
  };

  rc = sqlite3_open(":memory:", &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  for (i = 0; commands[i]; i++) {
    rc = sqlite3_exec(db, commands[i], callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error on %d: %s\n", i, zErrMsg);
      sqlite3_free(zErrMsg);
      exit(1);
    }
  }
  sqlite3_close(db);
  return 0;
}