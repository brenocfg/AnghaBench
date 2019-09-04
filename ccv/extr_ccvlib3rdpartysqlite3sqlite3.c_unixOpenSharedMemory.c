#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bProcessLock; struct unixShmNode* pShmNode; } ;
typedef  TYPE_1__ unixInodeInfo ;
struct TYPE_8__ {char* zPath; struct unixShmNode* pShm; TYPE_1__* pInode; int /*<<< orphan*/  h; } ;
typedef  TYPE_2__ unixFile ;
struct unixShmNode {char* zFilename; int h; scalar_t__ mutex; int isReadonly; struct unixShmNode* pFirst; struct unixShmNode* pNext; int /*<<< orphan*/  nRef; struct unixShmNode* pShmNode; TYPE_1__* pInode; } ;
struct unixShm {char* zFilename; int h; scalar_t__ mutex; int isReadonly; struct unixShm* pFirst; struct unixShm* pNext; int /*<<< orphan*/  nRef; struct unixShm* pShmNode; TYPE_1__* pInode; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
struct TYPE_9__ {scalar_t__ bCoreMutex; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SQLITE_CANTOPEN_BKPT ; 
 int SQLITE_IOERR_FSTAT ; 
 int /*<<< orphan*/  SQLITE_MUTEX_FAST ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_READONLY_CANTINIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct unixShmNode*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osFstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  robustFchown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* robust_open (char*,int,int) ; 
 int /*<<< orphan*/  sqlite3FileSuffix3 (char*,char*) ; 
 TYPE_6__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3_free (struct unixShmNode*) ; 
 struct unixShmNode* sqlite3_malloc64 (int) ; 
 scalar_t__ sqlite3_mutex_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 scalar_t__ sqlite3_uri_boolean (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  unixEnterMutex () ; 
 int /*<<< orphan*/  unixLeaveMutex () ; 
 int unixLockSharedMemory (TYPE_2__*,struct unixShmNode*) ; 
 int unixLogError (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  unixShmPurge (TYPE_2__*) ; 

__attribute__((used)) static int unixOpenSharedMemory(unixFile *pDbFd){
  struct unixShm *p = 0;          /* The connection to be opened */
  struct unixShmNode *pShmNode;   /* The underlying mmapped file */
  int rc = SQLITE_OK;             /* Result code */
  unixInodeInfo *pInode;          /* The inode of fd */
  char *zShm;             /* Name of the file used for SHM */
  int nShmFilename;               /* Size of the SHM filename in bytes */

  /* Allocate space for the new unixShm object. */
  p = sqlite3_malloc64( sizeof(*p) );
  if( p==0 ) return SQLITE_NOMEM_BKPT;
  memset(p, 0, sizeof(*p));
  assert( pDbFd->pShm==0 );

  /* Check to see if a unixShmNode object already exists. Reuse an existing
  ** one if present. Create a new one if necessary.
  */
  unixEnterMutex();
  pInode = pDbFd->pInode;
  pShmNode = pInode->pShmNode;
  if( pShmNode==0 ){
    struct stat sStat;                 /* fstat() info for database file */
#ifndef SQLITE_SHM_DIRECTORY
    const char *zBasePath = pDbFd->zPath;
#endif

    /* Call fstat() to figure out the permissions on the database file. If
    ** a new *-shm file is created, an attempt will be made to create it
    ** with the same permissions.
    */
    if( osFstat(pDbFd->h, &sStat) ){
      rc = SQLITE_IOERR_FSTAT;
      goto shm_open_err;
    }

#ifdef SQLITE_SHM_DIRECTORY
    nShmFilename = sizeof(SQLITE_SHM_DIRECTORY) + 31;
#else
    nShmFilename = 6 + (int)strlen(zBasePath);
#endif
    pShmNode = sqlite3_malloc64( sizeof(*pShmNode) + nShmFilename );
    if( pShmNode==0 ){
      rc = SQLITE_NOMEM_BKPT;
      goto shm_open_err;
    }
    memset(pShmNode, 0, sizeof(*pShmNode)+nShmFilename);
    zShm = pShmNode->zFilename = (char*)&pShmNode[1];
#ifdef SQLITE_SHM_DIRECTORY
    sqlite3_snprintf(nShmFilename, zShm, 
                     SQLITE_SHM_DIRECTORY "/sqlite-shm-%x-%x",
                     (u32)sStat.st_ino, (u32)sStat.st_dev);
#else
    sqlite3_snprintf(nShmFilename, zShm, "%s-shm", zBasePath);
    sqlite3FileSuffix3(pDbFd->zPath, zShm);
#endif
    pShmNode->h = -1;
    pDbFd->pInode->pShmNode = pShmNode;
    pShmNode->pInode = pDbFd->pInode;
    if( sqlite3GlobalConfig.bCoreMutex ){
      pShmNode->mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
      if( pShmNode->mutex==0 ){
        rc = SQLITE_NOMEM_BKPT;
        goto shm_open_err;
      }
    }

    if( pInode->bProcessLock==0 ){
      if( 0==sqlite3_uri_boolean(pDbFd->zPath, "readonly_shm", 0) ){
        pShmNode->h = robust_open(zShm, O_RDWR|O_CREAT, (sStat.st_mode&0777));
      }
      if( pShmNode->h<0 ){
        pShmNode->h = robust_open(zShm, O_RDONLY, (sStat.st_mode&0777));
        if( pShmNode->h<0 ){
          rc = unixLogError(SQLITE_CANTOPEN_BKPT, "open", zShm);
          goto shm_open_err;
        }
        pShmNode->isReadonly = 1;
      }

      /* If this process is running as root, make sure that the SHM file
      ** is owned by the same user that owns the original database.  Otherwise,
      ** the original owner will not be able to connect.
      */
      robustFchown(pShmNode->h, sStat.st_uid, sStat.st_gid);

      rc = unixLockSharedMemory(pDbFd, pShmNode);
      if( rc!=SQLITE_OK && rc!=SQLITE_READONLY_CANTINIT ) goto shm_open_err;
    }
  }

  /* Make the new connection a child of the unixShmNode */
  p->pShmNode = pShmNode;
#ifdef SQLITE_DEBUG
  p->id = pShmNode->nextShmId++;
#endif
  pShmNode->nRef++;
  pDbFd->pShm = p;
  unixLeaveMutex();

  /* The reference count on pShmNode has already been incremented under
  ** the cover of the unixEnterMutex() mutex and the pointer from the
  ** new (struct unixShm) object to the pShmNode has been set. All that is
  ** left to do is to link the new object into the linked list starting
  ** at pShmNode->pFirst. This must be done while holding the pShmNode->mutex 
  ** mutex.
  */
  sqlite3_mutex_enter(pShmNode->mutex);
  p->pNext = pShmNode->pFirst;
  pShmNode->pFirst = p;
  sqlite3_mutex_leave(pShmNode->mutex);
  return rc;

  /* Jump here on any error */
shm_open_err:
  unixShmPurge(pDbFd);       /* This call frees pShmNode if required */
  sqlite3_free(p);
  unixLeaveMutex();
  return rc;
}