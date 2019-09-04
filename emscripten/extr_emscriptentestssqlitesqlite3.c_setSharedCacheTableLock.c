#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_11__ {scalar_t__ iTable; scalar_t__ eLock; struct TYPE_11__* pNext; TYPE_2__* pBtree; } ;
struct TYPE_10__ {TYPE_4__* pLock; } ;
struct TYPE_9__ {int sharable; TYPE_1__* db; TYPE_3__* pBt; } ;
struct TYPE_8__ {int flags; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;
typedef  TYPE_4__ BtLock ;

/* Variables and functions */
 scalar_t__ READ_LOCK ; 
 int SQLITE_NOMEM ; 
 scalar_t__ SQLITE_OK ; 
 int SQLITE_ReadUncommitted ; 
 scalar_t__ WRITE_LOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ querySharedCacheTableLock (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int sqlite3BtreeHoldsMutex (TYPE_2__*) ; 
 scalar_t__ sqlite3MallocZero (int) ; 

__attribute__((used)) static int setSharedCacheTableLock(Btree *p, Pgno iTable, u8 eLock){
  BtShared *pBt = p->pBt;
  BtLock *pLock = 0;
  BtLock *pIter;

  assert( sqlite3BtreeHoldsMutex(p) );
  assert( eLock==READ_LOCK || eLock==WRITE_LOCK );
  assert( p->db!=0 );

  /* A connection with the read-uncommitted flag set will never try to
  ** obtain a read-lock using this function. The only read-lock obtained
  ** by a connection in read-uncommitted mode is on the sqlite_master 
  ** table, and that lock is obtained in BtreeBeginTrans().  */
  assert( 0==(p->db->flags&SQLITE_ReadUncommitted) || eLock==WRITE_LOCK );

  /* This function should only be called on a sharable b-tree after it 
  ** has been determined that no other b-tree holds a conflicting lock.  */
  assert( p->sharable );
  assert( SQLITE_OK==querySharedCacheTableLock(p, iTable, eLock) );

  /* First search the list for an existing lock on this table. */
  for(pIter=pBt->pLock; pIter; pIter=pIter->pNext){
    if( pIter->iTable==iTable && pIter->pBtree==p ){
      pLock = pIter;
      break;
    }
  }

  /* If the above search did not find a BtLock struct associating Btree p
  ** with table iTable, allocate one and link it into the list.
  */
  if( !pLock ){
    pLock = (BtLock *)sqlite3MallocZero(sizeof(BtLock));
    if( !pLock ){
      return SQLITE_NOMEM;
    }
    pLock->iTable = iTable;
    pLock->pBtree = p;
    pLock->pNext = pBt->pLock;
    pBt->pLock = pLock;
  }

  /* Set the BtLock.eLock variable to the maximum of the current lock
  ** and the requested lock. This means if a write-lock was already held
  ** and a read-lock requested, we don't incorrectly downgrade the lock.
  */
  assert( WRITE_LOCK>READ_LOCK );
  if( eLock>pLock->eLock ){
    pLock->eLock = eLock;
  }

  return SQLITE_OK;
}