#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ h; int /*<<< orphan*/  mutex; TYPE_3__* pFirst; TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixShmNode ;
struct TYPE_8__ {int exclMask; int sharedMask; int /*<<< orphan*/  id; struct TYPE_8__* pNext; TYPE_2__* pShmNode; } ;
typedef  TYPE_3__ unixShm ;
struct TYPE_9__ {TYPE_1__* pInode; TYPE_3__* pShm; } ;
typedef  TYPE_4__ unixFile ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_6__ {int bProcessLock; TYPE_2__* pShmNode; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int SQLITE_BUSY ; 
 int SQLITE_OK ; 
 int SQLITE_SHM_EXCLUSIVE ; 
 int SQLITE_SHM_LOCK ; 
 int SQLITE_SHM_NLOCK ; 
 int SQLITE_SHM_SHARED ; 
 int SQLITE_SHM_UNLOCK ; 
 scalar_t__ UNIX_SHM_BASE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  osGetpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int unixShmSystemLock (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int unixShmLock(
  sqlite3_file *fd,          /* Database file holding the shared memory */
  int ofst,                  /* First lock to acquire or release */
  int n,                     /* Number of locks to acquire or release */
  int flags                  /* What to do with the lock */
){
  unixFile *pDbFd = (unixFile*)fd;      /* Connection holding shared memory */
  unixShm *p = pDbFd->pShm;             /* The shared memory being locked */
  unixShm *pX;                          /* For looping over all siblings */
  unixShmNode *pShmNode = p->pShmNode;  /* The underlying file iNode */
  int rc = SQLITE_OK;                   /* Result code */
  u16 mask;                             /* Mask of locks to take or release */

  assert( pShmNode==pDbFd->pInode->pShmNode );
  assert( pShmNode->pInode==pDbFd->pInode );
  assert( ofst>=0 && ofst+n<=SQLITE_SHM_NLOCK );
  assert( n>=1 );
  assert( flags==(SQLITE_SHM_LOCK | SQLITE_SHM_SHARED)
       || flags==(SQLITE_SHM_LOCK | SQLITE_SHM_EXCLUSIVE)
       || flags==(SQLITE_SHM_UNLOCK | SQLITE_SHM_SHARED)
       || flags==(SQLITE_SHM_UNLOCK | SQLITE_SHM_EXCLUSIVE) );
  assert( n==1 || (flags & SQLITE_SHM_EXCLUSIVE)!=0 );
  assert( pShmNode->h>=0 || pDbFd->pInode->bProcessLock==1 );
  assert( pShmNode->h<0 || pDbFd->pInode->bProcessLock==0 );

  mask = (1<<(ofst+n)) - (1<<ofst);
  assert( n>1 || mask==(1<<ofst) );
  sqlite3_mutex_enter(pShmNode->mutex);
  if( flags & SQLITE_SHM_UNLOCK ){
    u16 allMask = 0; /* Mask of locks held by siblings */

    /* See if any siblings hold this same lock */
    for(pX=pShmNode->pFirst; pX; pX=pX->pNext){
      if( pX==p ) continue;
      assert( (pX->exclMask & (p->exclMask|p->sharedMask))==0 );
      allMask |= pX->sharedMask;
    }

    /* Unlock the system-level locks */
    if( (mask & allMask)==0 ){
      rc = unixShmSystemLock(pDbFd, F_UNLCK, ofst+UNIX_SHM_BASE, n);
    }else{
      rc = SQLITE_OK;
    }

    /* Undo the local locks */
    if( rc==SQLITE_OK ){
      p->exclMask &= ~mask;
      p->sharedMask &= ~mask;
    } 
  }else if( flags & SQLITE_SHM_SHARED ){
    u16 allShared = 0;  /* Union of locks held by connections other than "p" */

    /* Find out which shared locks are already held by sibling connections.
    ** If any sibling already holds an exclusive lock, go ahead and return
    ** SQLITE_BUSY.
    */
    for(pX=pShmNode->pFirst; pX; pX=pX->pNext){
      if( (pX->exclMask & mask)!=0 ){
        rc = SQLITE_BUSY;
        break;
      }
      allShared |= pX->sharedMask;
    }

    /* Get shared locks at the system level, if necessary */
    if( rc==SQLITE_OK ){
      if( (allShared & mask)==0 ){
        rc = unixShmSystemLock(pDbFd, F_RDLCK, ofst+UNIX_SHM_BASE, n);
      }else{
        rc = SQLITE_OK;
      }
    }

    /* Get the local shared locks */
    if( rc==SQLITE_OK ){
      p->sharedMask |= mask;
    }
  }else{
    /* Make sure no sibling connections hold locks that will block this
    ** lock.  If any do, return SQLITE_BUSY right away.
    */
    for(pX=pShmNode->pFirst; pX; pX=pX->pNext){
      if( (pX->exclMask & mask)!=0 || (pX->sharedMask & mask)!=0 ){
        rc = SQLITE_BUSY;
        break;
      }
    }
  
    /* Get the exclusive locks at the system level.  Then if successful
    ** also mark the local connection as being locked.
    */
    if( rc==SQLITE_OK ){
      rc = unixShmSystemLock(pDbFd, F_WRLCK, ofst+UNIX_SHM_BASE, n);
      if( rc==SQLITE_OK ){
        assert( (p->sharedMask & mask)==0 );
        p->exclMask |= mask;
      }
    }
  }
  sqlite3_mutex_leave(pShmNode->mutex);
  OSTRACE(("SHM-LOCK shmid-%d, pid-%d got %03x,%03x\n",
           p->id, osGetpid(0), p->sharedMask, p->exclMask));
  return rc;
}