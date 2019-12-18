#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_16__ {int rc; char const* zErrMsg; TYPE_2__* db; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pBt; } ;
typedef  TYPE_3__ Parse ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_2__*,int,char*,...) ; 
 int sqlite3FindDbName (TYPE_2__*,char const*) ; 
 scalar_t__ sqlite3OpenTempDatabase (TYPE_3__*) ; 
 TYPE_3__* sqlite3StackAllocZero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3StackFree (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static Btree *findBtree(sqlite3 *pErrorDb, sqlite3 *pDb, const char *zDb){
  int i = sqlite3FindDbName(pDb, zDb);

  if( i==1 ){
    Parse *pParse;
    int rc = 0;
    pParse = sqlite3StackAllocZero(pErrorDb, sizeof(*pParse));
    if( pParse==0 ){
      sqlite3Error(pErrorDb, SQLITE_NOMEM, "out of memory");
      rc = SQLITE_NOMEM;
    }else{
      pParse->db = pDb;
      if( sqlite3OpenTempDatabase(pParse) ){
        sqlite3Error(pErrorDb, pParse->rc, "%s", pParse->zErrMsg);
        rc = SQLITE_ERROR;
      }
      sqlite3DbFree(pErrorDb, pParse->zErrMsg);
      sqlite3StackFree(pErrorDb, pParse);
    }
    if( rc ){
      return 0;
    }
  }

  if( i<0 ){
    sqlite3Error(pErrorDb, SQLITE_ERROR, "unknown database %s", zDb);
    return 0;
  }

  return pDb->aDb[i].pBt;
}