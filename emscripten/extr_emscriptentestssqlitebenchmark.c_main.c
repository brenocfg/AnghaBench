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
 int atoi (char*) ; 
 int /*<<< orphan*/  callback ; 
 double emscripten_get_now () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int print ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 
 int test () ; 

int main(int argc, char **argv){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc, i;
  double t;
  int n, m;

  n = argc > 1 ? atoi(argv[1]) : 5000;
  m = argc > 2 ? atoi(argv[2]) : 1;

  rc = sqlite3_open(":memory:", &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }

  #define RUN(cmd) \
    { \
      rc = sqlite3_exec(db, cmd, callback, 0, &zErrMsg); \
      if( rc!=SQLITE_OK ){ \
        fprintf(stderr, "SQL error on %d: %s\n", i, zErrMsg); \
        sqlite3_free(zErrMsg); \
        exit(1); \
      } \
    }

  #define TIME(msg) \
    { \
      double now = emscripten_get_now(); \
      printf(msg " : took %f ms\n", now - t); \
      t = now; \
    }

  t = emscripten_get_now();
  TIME("'startup' - IGNORE THIS VALUE, it is an artifact");

  RUN("CREATE TABLE t1(a INTEGER, b INTEGER, c VARCHAR(100));");
  TIME("create table");

  RUN("BEGIN;");

  // n*5 INSERTs in a transaction
  for (i = 0; i < n; i++) {
    RUN("INSERT INTO t1 VALUES(1,12345,'one 1 one 1 one 1');");
    RUN("INSERT INTO t1 VALUES(2,23422,'two two two two');");
    RUN("INSERT INTO t1 VALUES(3,31233,'three three 33333333333 three');");
    RUN("INSERT INTO t1 VALUES(4,41414,'FOUR four 4 phor FOUR 44444');");
    RUN("INSERT INTO t1 VALUES(5,52555,'five 5 FIVE Five phayve 55 5 5 5 5 55  5');");
  }
  TIME("25,000 inserts");

  RUN("COMMIT;");
  TIME("commit");

  // Counts
  for (i = 0; i < m; i++) {
    print = i == 0;
    RUN("SELECT count(*) FROM t1;");
    RUN("SELECT count(*) FROM t1 WHERE a == 4");
    RUN("SELECT count(*) FROM t1 WHERE b > 20000 AND b < 50000;");
    RUN("SELECT count(*) FROM t1 WHERE c like '%three%';");
  }
  TIME("selects");

  // Index
  RUN("CREATE INDEX iiaa ON t1(a);");
  RUN("CREATE INDEX iibb ON t1(b);");
  TIME("create indexes");

  for (i = 0; i < m; i++) {
    print = i == 0;
    RUN("SELECT count(*) FROM t1 WHERE a == 4");
    RUN("SELECT count(*) FROM t1 WHERE b > 20000 AND b < 50000;");
  }
  TIME("selects with indexes");

  sqlite3_close(db);

  return test();
}