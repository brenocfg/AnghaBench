#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* pUnused; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_9__ {int fd; int flags; } ;
typedef  TYPE_2__ UnixUnusedFd ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 int MAX_PATHNAME ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_LARGEFILE ; 
 int O_NOFOLLOW ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SQLITE_CANTOPEN_BKPT ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_EXCLUSIVE ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_MASTER_JOURNAL ; 
 int SQLITE_OPEN_READONLY ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_SUBJOURNAL ; 
 int SQLITE_OPEN_TEMP_DB ; 
 int SQLITE_OPEN_TEMP_JOURNAL ; 
 int SQLITE_OPEN_TRANSIENT_DB ; 
 int SQLITE_OPEN_WAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int fillInUnixFile (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,char const*,int,int,int) ; 
 int findCreateFileMode (char const*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* findReusableFd (char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int openDirectory (char const*,int*) ; 
 int /*<<< orphan*/  robust_close (TYPE_1__*,int,int) ; 
 int robust_open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 TYPE_2__* sqlite3_malloc (int) ; 
 int unixGetTempname (int,char*) ; 
 int unixLogError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static int unixOpen(
  sqlite3_vfs *pVfs,           /* The VFS for which this is the xOpen method */
  const char *zPath,           /* Pathname of file to be opened */
  sqlite3_file *pFile,         /* The file descriptor to be filled in */
  int flags,                   /* Input flags to control the opening */
  int *pOutFlags               /* Output flags returned to SQLite core */
){
  unixFile *p = (unixFile *)pFile;
  int fd = -1;                   /* File descriptor returned by open() */
  int dirfd = -1;                /* Directory file descriptor */
  int openFlags = 0;             /* Flags to pass to open() */
  int eType = flags&0xFFFFFF00;  /* Type of file to open */
  int noLock;                    /* True to omit locking primitives */
  int rc = SQLITE_OK;            /* Function Return Code */

  int isExclusive  = (flags & SQLITE_OPEN_EXCLUSIVE);
  int isDelete     = (flags & SQLITE_OPEN_DELETEONCLOSE);
  int isCreate     = (flags & SQLITE_OPEN_CREATE);
  int isReadonly   = (flags & SQLITE_OPEN_READONLY);
  int isReadWrite  = (flags & SQLITE_OPEN_READWRITE);
#if SQLITE_ENABLE_LOCKING_STYLE
  int isAutoProxy  = (flags & SQLITE_OPEN_AUTOPROXY);
#endif

  /* If creating a master or main-file journal, this function will open
  ** a file-descriptor on the directory too. The first time unixSync()
  ** is called the directory file descriptor will be fsync()ed and close()d.
  */
  int isOpenDirectory = (isCreate && (
        eType==SQLITE_OPEN_MASTER_JOURNAL 
     || eType==SQLITE_OPEN_MAIN_JOURNAL 
     || eType==SQLITE_OPEN_WAL
  ));

  /* If argument zPath is a NULL pointer, this function is required to open
  ** a temporary file. Use this buffer to store the file name in.
  */
  char zTmpname[MAX_PATHNAME+1];
  const char *zName = zPath;

  /* Check the following statements are true: 
  **
  **   (a) Exactly one of the READWRITE and READONLY flags must be set, and 
  **   (b) if CREATE is set, then READWRITE must also be set, and
  **   (c) if EXCLUSIVE is set, then CREATE must also be set.
  **   (d) if DELETEONCLOSE is set, then CREATE must also be set.
  */
  assert((isReadonly==0 || isReadWrite==0) && (isReadWrite || isReadonly));
  assert(isCreate==0 || isReadWrite);
  assert(isExclusive==0 || isCreate);
  assert(isDelete==0 || isCreate);

  /* The main DB, main journal, WAL file and master journal are never 
  ** automatically deleted. Nor are they ever temporary files.  */
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_DB );
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MAIN_JOURNAL );
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_MASTER_JOURNAL );
  assert( (!isDelete && zName) || eType!=SQLITE_OPEN_WAL );

  /* Assert that the upper layer has set one of the "file-type" flags. */
  assert( eType==SQLITE_OPEN_MAIN_DB      || eType==SQLITE_OPEN_TEMP_DB 
       || eType==SQLITE_OPEN_MAIN_JOURNAL || eType==SQLITE_OPEN_TEMP_JOURNAL 
       || eType==SQLITE_OPEN_SUBJOURNAL   || eType==SQLITE_OPEN_MASTER_JOURNAL 
       || eType==SQLITE_OPEN_TRANSIENT_DB || eType==SQLITE_OPEN_WAL
  );

  memset(p, 0, sizeof(unixFile));

  if( eType==SQLITE_OPEN_MAIN_DB ){
    UnixUnusedFd *pUnused;
    pUnused = findReusableFd(zName, flags);
    if( pUnused ){
      fd = pUnused->fd;
    }else{
      pUnused = sqlite3_malloc(sizeof(*pUnused));
      if( !pUnused ){
        return SQLITE_NOMEM;
      }
    }
    p->pUnused = pUnused;
  }else if( !zName ){
    /* If zName is NULL, the upper layer is requesting a temp file. */
    assert(isDelete && !isOpenDirectory);
    rc = unixGetTempname(MAX_PATHNAME+1, zTmpname);
    if( rc!=SQLITE_OK ){
      return rc;
    }
    zName = zTmpname;
  }

  /* Determine the value of the flags parameter passed to POSIX function
  ** open(). These must be calculated even if open() is not called, as
  ** they may be stored as part of the file handle and used by the 
  ** 'conch file' locking functions later on.  */
  if( isReadonly )  openFlags |= O_RDONLY;
  if( isReadWrite ) openFlags |= O_RDWR;
  if( isCreate )    openFlags |= O_CREAT;
  if( isExclusive ) openFlags |= (O_EXCL|O_NOFOLLOW);
  openFlags |= (O_LARGEFILE|O_BINARY);

  if( fd<0 ){
    mode_t openMode;              /* Permissions to create file with */
    rc = findCreateFileMode(zName, flags, &openMode);
    if( rc!=SQLITE_OK ){
      assert( !p->pUnused );
      assert( eType==SQLITE_OPEN_WAL || eType==SQLITE_OPEN_MAIN_JOURNAL );
      return rc;
    }
    fd = robust_open(zName, openFlags, openMode);
    OSTRACE(("OPENX   %-3d %s 0%o\n", fd, zName, openFlags));
    if( fd<0 && errno!=EISDIR && isReadWrite && !isExclusive ){
      /* Failed to open the file for read/write access. Try read-only. */
      flags &= ~(SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
      openFlags &= ~(O_RDWR|O_CREAT);
      flags |= SQLITE_OPEN_READONLY;
      openFlags |= O_RDONLY;
      isReadonly = 1;
      fd = robust_open(zName, openFlags, openMode);
    }
    if( fd<0 ){
      rc = unixLogError(SQLITE_CANTOPEN_BKPT, "open", zName);
      goto open_finished;
    }
  }
  assert( fd>=0 );
  if( pOutFlags ){
    *pOutFlags = flags;
  }

  if( p->pUnused ){
    p->pUnused->fd = fd;
    p->pUnused->flags = flags;
  }

  if( isDelete ){
#if OS_VXWORKS
    zPath = zName;
#else
    unlink(zName);
#endif
  }
#if SQLITE_ENABLE_LOCKING_STYLE
  else{
    p->openFlags = openFlags;
  }
#endif

  if( isOpenDirectory ){
    rc = openDirectory(zPath, &dirfd);
    if( rc!=SQLITE_OK ){
      /* It is safe to close fd at this point, because it is guaranteed not
      ** to be open on a database file. If it were open on a database file,
      ** it would not be safe to close as this would release any locks held
      ** on the file by this process.  */
      assert( eType!=SQLITE_OPEN_MAIN_DB );
      robust_close(p, fd, __LINE__);
      goto open_finished;
    }
  }

#ifdef FD_CLOEXEC
  osFcntl(fd, F_SETFD, osFcntl(fd, F_GETFD, 0) | FD_CLOEXEC);
#endif

  noLock = eType!=SQLITE_OPEN_MAIN_DB;

  
#if defined(__APPLE__) || SQLITE_ENABLE_LOCKING_STYLE
  struct statfs fsInfo;
  if( fstatfs(fd, &fsInfo) == -1 ){
    ((unixFile*)pFile)->lastErrno = errno;
    if( dirfd>=0 ) robust_close(p, dirfd, __LINE__);
    robust_close(p, fd, __LINE__);
    return SQLITE_IOERR_ACCESS;
  }
  if (0 == strncmp("msdos", fsInfo.f_fstypename, 5)) {
    ((unixFile*)pFile)->fsFlags |= SQLITE_FSFLAGS_IS_MSDOS;
  }
#endif
  
#if SQLITE_ENABLE_LOCKING_STYLE
#if SQLITE_PREFER_PROXY_LOCKING
  isAutoProxy = 1;
#endif
  if( isAutoProxy && (zPath!=NULL) && (!noLock) && pVfs->xOpen ){
    char *envforce = getenv("SQLITE_FORCE_PROXY_LOCKING");
    int useProxy = 0;

    /* SQLITE_FORCE_PROXY_LOCKING==1 means force always use proxy, 0 means 
    ** never use proxy, NULL means use proxy for non-local files only.  */
    if( envforce!=NULL ){
      useProxy = atoi(envforce)>0;
    }else{
      struct statfs fsInfo;
      if( statfs(zPath, &fsInfo) == -1 ){
        /* In theory, the close(fd) call is sub-optimal. If the file opened
        ** with fd is a database file, and there are other connections open
        ** on that file that are currently holding advisory locks on it,
        ** then the call to close() will cancel those locks. In practice,
        ** we're assuming that statfs() doesn't fail very often. At least
        ** not while other file descriptors opened by the same process on
        ** the same file are working.  */
        p->lastErrno = errno;
        if( dirfd>=0 ){
          robust_close(p, dirfd, __LINE__);
        }
        robust_close(p, fd, __LINE__);
        rc = SQLITE_IOERR_ACCESS;
        goto open_finished;
      }
      useProxy = !(fsInfo.f_flags&MNT_LOCAL);
    }
    if( useProxy ){
      rc = fillInUnixFile(pVfs, fd, dirfd, pFile, zPath, noLock,
                          isDelete, isReadonly);
      if( rc==SQLITE_OK ){
        rc = proxyTransformUnixFile((unixFile*)pFile, ":auto:");
        if( rc!=SQLITE_OK ){
          /* Use unixClose to clean up the resources added in fillInUnixFile 
          ** and clear all the structure's references.  Specifically, 
          ** pFile->pMethods will be NULL so sqlite3OsClose will be a no-op 
          */
          unixClose(pFile);
          return rc;
        }
      }
      goto open_finished;
    }
  }
#endif
  
  rc = fillInUnixFile(pVfs, fd, dirfd, pFile, zPath, noLock,
                      isDelete, isReadonly);
open_finished:
  if( rc!=SQLITE_OK ){
    sqlite3_free(p->pUnused);
  }
  return rc;
}