#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_1__ Table ;
struct TYPE_15__ {int /*<<< orphan*/  zName; } ;
struct TYPE_14__ {int nTab; scalar_t__ nMem; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  analyzeOneTable (TYPE_2__*,TYPE_1__*,TYPE_3__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  loadAnalysis (TYPE_2__*,int) ; 
 int /*<<< orphan*/  openStatTable (TYPE_2__*,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3BeginWriteOperation (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3BtreeHoldsAllMutexes (int /*<<< orphan*/ ) ; 
 int sqlite3SchemaToIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void analyzeTable(Parse *pParse, Table *pTab, Index *pOnlyIdx){
  int iDb;
  int iStatCur;

  assert( pTab!=0 );
  assert( sqlite3BtreeHoldsAllMutexes(pParse->db) );
  iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
  sqlite3BeginWriteOperation(pParse, 0, iDb);
  iStatCur = pParse->nTab;
  pParse->nTab += 3;
  if( pOnlyIdx ){
    openStatTable(pParse, iDb, iStatCur, pOnlyIdx->zName, "idx");
  }else{
    openStatTable(pParse, iDb, iStatCur, pTab->zName, "tbl");
  }
  analyzeOneTable(pParse, pTab, pOnlyIdx, iStatCur,pParse->nMem+1,pParse->nTab);
  loadAnalysis(pParse, iDb);
}