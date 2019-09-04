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
struct TYPE_2__ {int szTest; int /*<<< orphan*/  pStmt; int /*<<< orphan*/  zResult; scalar_t__ bVerify; } ;

/* Variables and functions */
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*,unsigned int,unsigned int,unsigned int,int,int) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/  speedtest1_begin_test (int,char*,...) ; 
 int /*<<< orphan*/  speedtest1_end_test () ; 
 int /*<<< orphan*/  speedtest1_exec (char*) ; 
 int /*<<< orphan*/  speedtest1_execute () ; 
 int /*<<< orphan*/  speedtest1_prepare (char*) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,unsigned int) ; 
 int* sqlite3_malloc (int) ; 
 int /*<<< orphan*/  twoCoords (int,int,unsigned int,unsigned int*,unsigned int*) ; 

void testset_rtree(int p1, int p2){
  unsigned i, n;
  unsigned mxCoord;
  unsigned x0, x1, y0, y1, z0, z1;
  unsigned iStep;
  int *aCheck = sqlite3_malloc( sizeof(int)*g.szTest*100 );

  mxCoord = 15000;
  n = g.szTest*100;
  speedtest1_begin_test(100, "%d INSERTs into an r-tree", n);
  speedtest1_exec("BEGIN");
  speedtest1_exec("CREATE VIRTUAL TABLE rt1 USING rtree(id,x0,x1,y0,y1,z0,z1)");
  speedtest1_prepare("INSERT INTO rt1(id,x0,x1,y0,y1,z0,z1)"
                     "VALUES(?1,?2,?3,?4,?5,?6,?7)");
  for(i=1; i<=n; i++){
    twoCoords(p1, p2, mxCoord, &x0, &x1);
    twoCoords(p1, p2, mxCoord, &y0, &y1);
    twoCoords(p1, p2, mxCoord, &z0, &z1);
    sqlite3_bind_int(g.pStmt, 1, i);
    sqlite3_bind_int(g.pStmt, 2, x0);
    sqlite3_bind_int(g.pStmt, 3, x1);
    sqlite3_bind_int(g.pStmt, 4, y0);
    sqlite3_bind_int(g.pStmt, 5, y1);
    sqlite3_bind_int(g.pStmt, 6, z0);
    sqlite3_bind_int(g.pStmt, 7, z1);
    speedtest1_execute();
  }
  speedtest1_exec("COMMIT");
  speedtest1_end_test();

  speedtest1_begin_test(101, "Copy from rtree to a regular table");
  speedtest1_exec("CREATE TABLE t1(id INTEGER PRIMARY KEY,x0,x1,y0,y1,z0,z1)");
  speedtest1_exec("INSERT INTO t1 SELECT * FROM rt1");
  speedtest1_end_test();

  n = g.szTest*20;
  speedtest1_begin_test(110, "%d one-dimensional intersect slice queries", n);
  speedtest1_prepare("SELECT count(*) FROM rt1 WHERE x0>=?1 AND x1<=?2");
  iStep = mxCoord/n;
  for(i=0; i<n; i++){
    sqlite3_bind_int(g.pStmt, 1, i*iStep);
    sqlite3_bind_int(g.pStmt, 2, (i+1)*iStep);
    speedtest1_execute();
    aCheck[i] = atoi(g.zResult);
  }
  speedtest1_end_test();

  if( g.bVerify ){
    n = g.szTest*20;
    speedtest1_begin_test(111, "Verify result from 1-D intersect slice queries");
    speedtest1_prepare("SELECT count(*) FROM t1 WHERE x0>=?1 AND x1<=?2");
    iStep = mxCoord/n;
    for(i=0; i<n; i++){
      sqlite3_bind_int(g.pStmt, 1, i*iStep);
      sqlite3_bind_int(g.pStmt, 2, (i+1)*iStep);
      speedtest1_execute();
      if( aCheck[i]!=atoi(g.zResult) ){
        fatal_error("Count disagree step %d: %d..%d.  %d vs %d",
                    i, i*iStep, (i+1)*iStep, aCheck[i], atoi(g.zResult));
      }
    }
    speedtest1_end_test();
  }
  
  n = g.szTest*20;
  speedtest1_begin_test(120, "%d one-dimensional overlap slice queries", n);
  speedtest1_prepare("SELECT count(*) FROM rt1 WHERE y1>=?1 AND y0<=?2");
  iStep = mxCoord/n;
  for(i=0; i<n; i++){
    sqlite3_bind_int(g.pStmt, 1, i*iStep);
    sqlite3_bind_int(g.pStmt, 2, (i+1)*iStep);
    speedtest1_execute();
    aCheck[i] = atoi(g.zResult);
  }
  speedtest1_end_test();

  if( g.bVerify ){
    n = g.szTest*20;
    speedtest1_begin_test(121, "Verify result from 1-D overlap slice queries");
    speedtest1_prepare("SELECT count(*) FROM t1 WHERE y1>=?1 AND y0<=?2");
    iStep = mxCoord/n;
    for(i=0; i<n; i++){
      sqlite3_bind_int(g.pStmt, 1, i*iStep);
      sqlite3_bind_int(g.pStmt, 2, (i+1)*iStep);
      speedtest1_execute();
      if( aCheck[i]!=atoi(g.zResult) ){
        fatal_error("Count disagree step %d: %d..%d.  %d vs %d",
                    i, i*iStep, (i+1)*iStep, aCheck[i], atoi(g.zResult));
      }
    }
    speedtest1_end_test();
  }
  

  n = g.szTest*20;
  speedtest1_begin_test(125, "%d custom geometry callback queries", n);
  //sqlite3_rtree_geometry_callback(g.db, "xslice", xsliceGeometryCallback, 0);
  speedtest1_prepare("SELECT count(*) FROM rt1 WHERE id MATCH xslice(?1,?2)");
  iStep = mxCoord/n;
  for(i=0; i<n; i++){
    sqlite3_bind_int(g.pStmt, 1, i*iStep);
    sqlite3_bind_int(g.pStmt, 2, (i+1)*iStep);
    speedtest1_execute();
    if( aCheck[i]!=atoi(g.zResult) ){
      fatal_error("Count disagree step %d: %d..%d.  %d vs %d",
                  i, i*iStep, (i+1)*iStep, aCheck[i], atoi(g.zResult));
    }
  }
  speedtest1_end_test();

  n = g.szTest*80;
  speedtest1_begin_test(130, "%d three-dimensional intersect box queries", n);
  speedtest1_prepare("SELECT count(*) FROM rt1 WHERE x1>=?1 AND x0<=?2"
                     " AND y1>=?1 AND y0<=?2 AND z1>=?1 AND z0<=?2");
  iStep = mxCoord/n;
  for(i=0; i<n; i++){
    sqlite3_bind_int(g.pStmt, 1, i*iStep);
    sqlite3_bind_int(g.pStmt, 2, (i+1)*iStep);
    speedtest1_execute();
    aCheck[i] = atoi(g.zResult);
  }
  speedtest1_end_test();

  n = g.szTest*100;
  speedtest1_begin_test(140, "%d rowid queries", n);
  speedtest1_prepare("SELECT * FROM rt1 WHERE id=?1");
  for(i=1; i<=n; i++){
    sqlite3_bind_int(g.pStmt, 1, i);
    speedtest1_execute();
  }
  speedtest1_end_test();
}