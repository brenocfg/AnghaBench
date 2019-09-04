#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_14__ {int nTab; int nMem; TYPE_2__* db; } ;
struct TYPE_13__ {int /*<<< orphan*/  tblHash; } ;
struct TYPE_11__ {TYPE_3__* pSchema; } ;
typedef  TYPE_3__ Schema ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  HashElem ;

/* Variables and functions */
 int /*<<< orphan*/  analyzeOneTable (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loadAnalysis (TYPE_4__*,int) ; 
 int /*<<< orphan*/  openStatTable (TYPE_4__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BeginWriteOperation (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3SchemaMutexHeld (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void analyzeDatabase(Parse *pParse, int iDb){
  sqlite3 *db = pParse->db;
  Schema *pSchema = db->aDb[iDb].pSchema;    /* Schema of database iDb */
  HashElem *k;
  int iStatCur;
  int iMem;

  sqlite3BeginWriteOperation(pParse, 0, iDb);
  iStatCur = pParse->nTab;
  pParse->nTab += 3;
  openStatTable(pParse, iDb, iStatCur, 0, 0);
  iMem = pParse->nMem+1;
  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
  for(k=sqliteHashFirst(&pSchema->tblHash); k; k=sqliteHashNext(k)){
    Table *pTab = (Table*)sqliteHashData(k);
    analyzeOneTable(pParse, pTab, 0, iStatCur, iMem);
  }
  loadAnalysis(pParse, iDb);
}