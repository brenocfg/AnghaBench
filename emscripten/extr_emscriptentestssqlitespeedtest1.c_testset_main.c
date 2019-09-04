#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zNum ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_2__ {int szTest; int /*<<< orphan*/  pStmt; int /*<<< orphan*/  zWR; int /*<<< orphan*/  zNN; int /*<<< orphan*/  zPK; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int est_square_root (int) ; 
 TYPE_1__ g ; 
 int roundup_allones (int) ; 
 int /*<<< orphan*/  speedtest1_begin_test (int,char*,...) ; 
 int /*<<< orphan*/  speedtest1_end_test () ; 
 int /*<<< orphan*/  speedtest1_exec (char*,...) ; 
 int /*<<< orphan*/  speedtest1_execute () ; 
 int speedtest1_numbername (unsigned int,char*,int) ; 
 int /*<<< orphan*/  speedtest1_prepare (char*,...) ; 
 int speedtest1_random () ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 unsigned int swizzle (int,int) ; 

void testset_main(void){
  int i;                        /* Loop counter */
  int n;                        /* iteration count */
  int sz;                       /* Size of the tables */
  int maxb;                     /* Maximum swizzled value */
  unsigned x1, x2;              /* Parameters */
  int len;                      /* Length of the zNum[] string */
  char zNum[2000];              /* A number name */

  sz = n = g.szTest*500;
  maxb = roundup_allones(sz);
  speedtest1_begin_test(100, "%d INSERTs into table with no index", n);
  speedtest1_exec("BEGIN");
  speedtest1_exec("CREATE TABLE t1(a INTEGER %s, b INTEGER %s, c TEXT %s);",
                  g.zNN, g.zNN, g.zNN);
  speedtest1_prepare("INSERT INTO t1 VALUES(?1,?2,?3); --  %d times", n);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int64(g.pStmt, 1, (sqlite3_int64)x1);
    sqlite3_bind_int(g.pStmt, 2, i);
    sqlite3_bind_text(g.pStmt, 3, zNum, -1, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  speedtest1_begin_test(110, "%d ordered INSERTS with one index/PK", n);
  speedtest1_exec("BEGIN");
  speedtest1_exec("CREATE TABLE t2(a INTEGER %s %s, b INTEGER %s, c TEXT %s) %s",
                   g.zNN, g.zPK, g.zNN, g.zNN, g.zWR);
  speedtest1_prepare("INSERT INTO t2 VALUES(?1,?2,?3); -- %d times", n);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int(g.pStmt, 1, i);
    sqlite3_bind_int64(g.pStmt, 2, (sqlite3_int64)x1);
    sqlite3_bind_text(g.pStmt, 3, zNum, -1, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  speedtest1_begin_test(120, "%d unordered INSERTS with one index/PK", n);
  speedtest1_exec("BEGIN");
  speedtest1_exec("CREATE TABLE t3(a INTEGER %s %s, b INTEGER %s, c TEXT %s) %s",
                   g.zNN, g.zPK, g.zNN, g.zNN, g.zWR);
  speedtest1_prepare("INSERT INTO t3 VALUES(?1,?2,?3); -- %d times", n);
  for(i=1; i<=n; i++){
    x1 = swizzle(i,maxb);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    sqlite3_bind_int(g.pStmt, 2, i);
    sqlite3_bind_int64(g.pStmt, 1, (sqlite3_int64)x1);
    sqlite3_bind_text(g.pStmt, 3, zNum, -1, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = 25;
  speedtest1_begin_test(130, "%d SELECTS, numeric BETWEEN, unindexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT count(*), avg(b), sum(length(c)) FROM t1\n"
    " WHERE b BETWEEN ?1 AND ?2; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    sqlite3_bind_int(g.pStmt, 2, x2);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = 10;
  speedtest1_begin_test(140, "%d SELECTS, LIKE, unindexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT count(*), avg(b), sum(length(c)) FROM t1\n"
    " WHERE c LIKE ?1; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    zNum[0] = '%';
    len = speedtest1_numbername(i, zNum+1, sizeof(zNum)-2);
    zNum[len] = '%';
    zNum[len+1] = 0;
    sqlite3_bind_text(g.pStmt, 1, zNum, len, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = 10;
  speedtest1_begin_test(142, "%d SELECTS w/ORDER BY, unindexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT a, b, c FROM t1 WHERE c LIKE ?1\n"
    " ORDER BY a; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    zNum[0] = '%';
    len = speedtest1_numbername(i, zNum+1, sizeof(zNum)-2);
    zNum[len] = '%';
    zNum[len+1] = 0;
    sqlite3_bind_text(g.pStmt, 1, zNum, len, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = 10; //g.szTest/5;
  speedtest1_begin_test(145, "%d SELECTS w/ORDER BY and LIMIT, unindexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT a, b, c FROM t1 WHERE c LIKE ?1\n"
    " ORDER BY a LIMIT 10; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    zNum[0] = '%';
    len = speedtest1_numbername(i, zNum+1, sizeof(zNum)-2);
    zNum[len] = '%';
    zNum[len+1] = 0;
    sqlite3_bind_text(g.pStmt, 1, zNum, len, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  speedtest1_begin_test(150, "CREATE INDEX five times");
  speedtest1_exec("BEGIN;");
  speedtest1_exec("CREATE UNIQUE INDEX t1b ON t1(b);");
  speedtest1_exec("CREATE INDEX t1c ON t1(c);");
  speedtest1_exec("CREATE UNIQUE INDEX t2b ON t2(b);");
  speedtest1_exec("CREATE INDEX t2c ON t2(c DESC);");
  speedtest1_exec("CREATE INDEX t3bc ON t3(b,c);");
  speedtest1_exec("COMMIT;");
  speedtest1_end_test();


  n = sz/5;
  speedtest1_begin_test(160, "%d SELECTS, numeric BETWEEN, indexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT count(*), avg(b), sum(length(c)) FROM t1\n"
    " WHERE b BETWEEN ?1 AND ?2; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    sqlite3_bind_int(g.pStmt, 2, x2);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz/5;
  speedtest1_begin_test(161, "%d SELECTS, numeric BETWEEN, PK", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT count(*), avg(b), sum(length(c)) FROM t2\n"
    " WHERE a BETWEEN ?1 AND ?2; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    sqlite3_bind_int(g.pStmt, 2, x2);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz/5;
  speedtest1_begin_test(170, "%d SELECTS, text BETWEEN, indexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT count(*), avg(b), sum(length(c)) FROM t1\n"
    " WHERE c BETWEEN ?1 AND (?1||'~'); -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = swizzle(i, maxb);
    len = speedtest1_numbername(x1, zNum, sizeof(zNum)-1);
    sqlite3_bind_text(g.pStmt, 1, zNum, len, SQLITE_STATIC);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = sz;
  speedtest1_begin_test(180, "%d INSERTS with three indexes", n);
  speedtest1_exec("BEGIN");
  speedtest1_exec(
    "CREATE TABLE t4(\n"
    "  a INTEGER %s %s,\n"
    "  b INTEGER %s,\n"
    "  c TEXT %s\n"
    ") %s",
    g.zNN, g.zPK, g.zNN, g.zNN, g.zWR);
  speedtest1_exec("CREATE INDEX t4b ON t4(b)");
  speedtest1_exec("CREATE INDEX t4c ON t4(c)");
  speedtest1_exec("INSERT INTO t4 SELECT * FROM t1");
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  n = sz;
  speedtest1_begin_test(190, "DELETE and REFILL one table", n);
  speedtest1_exec("DELETE FROM t2;");
  speedtest1_exec("INSERT INTO t2 SELECT * FROM t1;");
  speedtest1_end_test();

//  #include <emscripten.h>
  speedtest1_begin_test(200, "VACUUM");
//  EM_ASM( alert('pre') );
  speedtest1_exec("VACUUM");
//  EM_ASM( alert('post') );
  speedtest1_end_test();


  speedtest1_begin_test(210, "ALTER TABLE ADD COLUMN, and query");
  speedtest1_exec("ALTER TABLE t2 ADD COLUMN d DEFAULT 123");
  speedtest1_exec("SELECT sum(d) FROM t2");
  speedtest1_end_test();


  n = sz/5;
  speedtest1_begin_test(230, "%d UPDATES, numeric BETWEEN, indexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "UPDATE t2 SET d=b*2 WHERE b BETWEEN ?1 AND ?2; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    sqlite3_bind_int(g.pStmt, 2, x2);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  speedtest1_begin_test(240, "%d UPDATES of individual rows", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "UPDATE t2 SET d=b*3 WHERE a=?1; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%sz + 1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  speedtest1_begin_test(250, "One big UPDATE of the whole %d-row table", sz);
  speedtest1_exec("UPDATE t2 SET d=b*4");
  speedtest1_end_test();


  speedtest1_begin_test(260, "Query added column after filling");
  speedtest1_exec("SELECT sum(d) FROM t2");
  speedtest1_end_test();



  n = sz/5;
  speedtest1_begin_test(270, "%d DELETEs, numeric BETWEEN, indexed", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "DELETE FROM t2 WHERE b BETWEEN ?1 AND ?2; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%maxb + 1;
    x2 = speedtest1_random()%10 + sz/5000 + x1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    sqlite3_bind_int(g.pStmt, 2, x2);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  n = sz;
  speedtest1_begin_test(280, "%d DELETEs of individual rows", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "DELETE FROM t3 WHERE a=?1; -- %d times", n
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%sz + 1;
    sqlite3_bind_int(g.pStmt, 1, x1);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();


  speedtest1_begin_test(290, "Refill two %d-row tables using REPLACE", sz);
  speedtest1_exec("REPLACE INTO t2(a,b,c) SELECT a,b,c FROM t1");
  speedtest1_exec("REPLACE INTO t3(a,b,c) SELECT a,b,c FROM t1");
  speedtest1_end_test();

  speedtest1_begin_test(300, "Refill a %d-row table using (b&1)==(a&1)", sz);
  speedtest1_exec("DELETE FROM t2;");
  speedtest1_exec("INSERT INTO t2(a,b,c)\n"
                  " SELECT a,b,c FROM t1  WHERE (b&1)==(a&1);");
  speedtest1_exec("INSERT INTO t2(a,b,c)\n"
                  " SELECT a,b,c FROM t1  WHERE (b&1)<>(a&1);");
  speedtest1_end_test();


  n = sz/5;
  speedtest1_begin_test(310, "%d four-ways joins", n);
  speedtest1_exec("BEGIN");
  speedtest1_prepare(
    "SELECT t1.c FROM t1, t2, t3, t4\n"
    " WHERE t4.a BETWEEN ?1 AND ?2\n"
    "   AND t3.a=t4.b\n"
    "   AND t2.a=t3.b\n"
    "   AND t1.c=t2.c"
  );
  for(i=1; i<=n; i++){
    x1 = speedtest1_random()%sz + 1;
    x2 = speedtest1_random()%10 + x1 + 4;
    sqlite3_bind_int(g.pStmt, 1, x1);
    sqlite3_bind_int(g.pStmt, 2, x2);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  speedtest1_begin_test(320, "subquery in result set", n);
  speedtest1_prepare(
    "SELECT sum(a), max(c),\n"
    "       avg((SELECT a FROM t2 WHERE 5+t2.b=t1.b) AND rowid<?1), max(c)\n"
    " FROM t1 WHERE rowid<?1;"
  );
  sqlite3_bind_int(g.pStmt, 1, est_square_root(g.szTest)*50);
  speedtest1_execute();
  speedtest1_end_test();

  speedtest1_begin_test(980, "PRAGMA integrity_check");
  speedtest1_exec("PRAGMA integrity_check");
  speedtest1_end_test();


  speedtest1_begin_test(990, "ANALYZE");
  speedtest1_exec("ANALYZE");
  speedtest1_end_test();
}