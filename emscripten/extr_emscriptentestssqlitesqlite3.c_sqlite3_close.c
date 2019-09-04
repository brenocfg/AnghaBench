#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct Db {TYPE_4__* pSchema; int /*<<< orphan*/ * pBt; } ;
struct TYPE_22__ {scalar_t__ nOut; TYPE_3__* pStart; scalar_t__ bMalloced; } ;
struct TYPE_21__ {TYPE_4__** a; } ;
struct TYPE_23__ {int nDb; TYPE_2__ lookaside; int /*<<< orphan*/  mutex; int /*<<< orphan*/  magic; struct Db* aDb; scalar_t__ pErr; int /*<<< orphan*/  aModule; int /*<<< orphan*/  aCollSeq; TYPE_1__ aFunc; struct Db* aDbStatic; scalar_t__ pVdbe; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_24__ {int /*<<< orphan*/  pAux; int /*<<< orphan*/  (* xDestroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pUser; int /*<<< orphan*/  (* xDel ) (int /*<<< orphan*/ ) ;struct TYPE_24__* pNext; struct TYPE_24__* pHash; } ;
typedef  TYPE_4__ Module ;
typedef  int /*<<< orphan*/  HashElem ;
typedef  TYPE_4__ FuncDef ;
typedef  TYPE_4__ CollSeq ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int ArraySize (TYPE_4__**) ; 
 int SQLITE_BUSY ; 
 int /*<<< orphan*/  SQLITE_MAGIC_CLOSED ; 
 int /*<<< orphan*/  SQLITE_MAGIC_ERROR ; 
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  functionDestroy (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3BtreeClose (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3BtreeIsInBackup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3CloseExtensions (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3CloseSavepoints (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ConnectionClosed (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  sqlite3HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ResetInternalSchema (TYPE_3__*,int) ; 
 int sqlite3SafetyCheckSickOrOk (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ValueFree (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VtabRollback (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int sqlite3_close(sqlite3 *db){
  HashElem *i;                    /* Hash table iterator */
  int j;

  if( !db ){
    return SQLITE_OK;
  }
  if( !sqlite3SafetyCheckSickOrOk(db) ){
    return SQLITE_MISUSE_BKPT;
  }
  sqlite3_mutex_enter(db->mutex);

  /* Force xDestroy calls on all virtual tables */
  sqlite3ResetInternalSchema(db, -1);

  /* If a transaction is open, the ResetInternalSchema() call above
  ** will not have called the xDisconnect() method on any virtual
  ** tables in the db->aVTrans[] array. The following sqlite3VtabRollback()
  ** call will do so. We need to do this before the check for active
  ** SQL statements below, as the v-table implementation may be storing
  ** some prepared statements internally.
  */
  sqlite3VtabRollback(db);

  /* If there are any outstanding VMs, return SQLITE_BUSY. */
  if( db->pVdbe ){
    sqlite3Error(db, SQLITE_BUSY, 
        "unable to close due to unfinalised statements");
    sqlite3_mutex_leave(db->mutex);
    return SQLITE_BUSY;
  }
  assert( sqlite3SafetyCheckSickOrOk(db) );

  for(j=0; j<db->nDb; j++){
    Btree *pBt = db->aDb[j].pBt;
    if( pBt && sqlite3BtreeIsInBackup(pBt) ){
      sqlite3Error(db, SQLITE_BUSY, 
          "unable to close due to unfinished backup operation");
      sqlite3_mutex_leave(db->mutex);
      return SQLITE_BUSY;
    }
  }

  /* Free any outstanding Savepoint structures. */
  sqlite3CloseSavepoints(db);

  for(j=0; j<db->nDb; j++){
    struct Db *pDb = &db->aDb[j];
    if( pDb->pBt ){
      sqlite3BtreeClose(pDb->pBt);
      pDb->pBt = 0;
      if( j!=1 ){
        pDb->pSchema = 0;
      }
    }
  }
  sqlite3ResetInternalSchema(db, -1);

  /* Tell the code in notify.c that the connection no longer holds any
  ** locks and does not require any further unlock-notify callbacks.
  */
  sqlite3ConnectionClosed(db);

  assert( db->nDb<=2 );
  assert( db->aDb==db->aDbStatic );
  for(j=0; j<ArraySize(db->aFunc.a); j++){
    FuncDef *pNext, *pHash, *p;
    for(p=db->aFunc.a[j]; p; p=pHash){
      pHash = p->pHash;
      while( p ){
        functionDestroy(db, p);
        pNext = p->pNext;
        sqlite3DbFree(db, p);
        p = pNext;
      }
    }
  }
  for(i=sqliteHashFirst(&db->aCollSeq); i; i=sqliteHashNext(i)){
    CollSeq *pColl = (CollSeq *)sqliteHashData(i);
    /* Invoke any destructors registered for collation sequence user data. */
    for(j=0; j<3; j++){
      if( pColl[j].xDel ){
        pColl[j].xDel(pColl[j].pUser);
      }
    }
    sqlite3DbFree(db, pColl);
  }
  sqlite3HashClear(&db->aCollSeq);
#ifndef SQLITE_OMIT_VIRTUALTABLE
  for(i=sqliteHashFirst(&db->aModule); i; i=sqliteHashNext(i)){
    Module *pMod = (Module *)sqliteHashData(i);
    if( pMod->xDestroy ){
      pMod->xDestroy(pMod->pAux);
    }
    sqlite3DbFree(db, pMod);
  }
  sqlite3HashClear(&db->aModule);
#endif

  sqlite3Error(db, SQLITE_OK, 0); /* Deallocates any cached error strings. */
  if( db->pErr ){
    sqlite3ValueFree(db->pErr);
  }
  sqlite3CloseExtensions(db);

  db->magic = SQLITE_MAGIC_ERROR;

  /* The temp-database schema is allocated differently from the other schema
  ** objects (using sqliteMalloc() directly, instead of sqlite3BtreeSchema()).
  ** So it needs to be freed here. Todo: Why not roll the temp schema into
  ** the same sqliteMalloc() as the one that allocates the database 
  ** structure?
  */
  sqlite3DbFree(db, db->aDb[1].pSchema);
  sqlite3_mutex_leave(db->mutex);
  db->magic = SQLITE_MAGIC_CLOSED;
  sqlite3_mutex_free(db->mutex);
  assert( db->lookaside.nOut==0 );  /* Fails on a lookaside memory leak */
  if( db->lookaside.bMalloced ){
    sqlite3_free(db->lookaside.pStart);
  }
  sqlite3_free(db);
  return SQLITE_OK;
}