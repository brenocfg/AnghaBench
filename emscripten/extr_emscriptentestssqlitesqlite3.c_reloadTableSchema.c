#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_12__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  pSchema; struct TYPE_12__* pNext; } ;
typedef  TYPE_1__ Trigger ;
struct TYPE_13__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_2__ Table ;
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  OP_DropTable ; 
 int /*<<< orphan*/  OP_DropTrigger ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BtreeHoldsAllMutexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_3__*) ; 
 char* sqlite3MPrintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int sqlite3SchemaToIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3TriggerList (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddParseSchemaOp (int /*<<< orphan*/ *,int,char*) ; 
 char* whereTempTriggers (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void reloadTableSchema(Parse *pParse, Table *pTab, const char *zName){
  Vdbe *v;
  char *zWhere;
  int iDb;                   /* Index of database containing pTab */
#ifndef SQLITE_OMIT_TRIGGER
  Trigger *pTrig;
#endif

  v = sqlite3GetVdbe(pParse);
  if( NEVER(v==0) ) return;
  assert( sqlite3BtreeHoldsAllMutexes(pParse->db) );
  iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
  assert( iDb>=0 );

#ifndef SQLITE_OMIT_TRIGGER
  /* Drop any table triggers from the internal schema. */
  for(pTrig=sqlite3TriggerList(pParse, pTab); pTrig; pTrig=pTrig->pNext){
    int iTrigDb = sqlite3SchemaToIndex(pParse->db, pTrig->pSchema);
    assert( iTrigDb==iDb || iTrigDb==1 );
    sqlite3VdbeAddOp4(v, OP_DropTrigger, iTrigDb, 0, 0, pTrig->zName, 0);
  }
#endif

  /* Drop the table and index from the internal schema.  */
  sqlite3VdbeAddOp4(v, OP_DropTable, iDb, 0, 0, pTab->zName, 0);

  /* Reload the table, index and permanent trigger schemas. */
  zWhere = sqlite3MPrintf(pParse->db, "tbl_name=%Q", zName);
  if( !zWhere ) return;
  sqlite3VdbeAddParseSchemaOp(v, iDb, zWhere);

#ifndef SQLITE_OMIT_TRIGGER
  /* Now, if the table is not stored in the temp database, reload any temp 
  ** triggers. Don't use IN(...) in case SQLITE_OMIT_SUBQUERY is defined. 
  */
  if( (zWhere=whereTempTriggers(pParse, pTab))!=0 ){
    sqlite3VdbeAddParseSchemaOp(v, 1, zWhere);
  }
#endif
}