#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eFileLock; int lastErrno; int szChunk; int /*<<< orphan*/  dbUpdate; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
#define  SQLITE_FCNTL_CHUNK_SIZE 133 
#define  SQLITE_FCNTL_DB_UNCHANGED 132 
#define  SQLITE_FCNTL_LOCKSTATE 131 
#define  SQLITE_FCNTL_SIZE_HINT 130 
#define  SQLITE_FCNTL_SYNC_OMITTED 129 
#define  SQLITE_LAST_ERRNO 128 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int fcntlSizeHint (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unixFileControl(sqlite3_file *id, int op, void *pArg){
  switch( op ){
    case SQLITE_FCNTL_LOCKSTATE: {
      *(int*)pArg = ((unixFile*)id)->eFileLock;
      return SQLITE_OK;
    }
    case SQLITE_LAST_ERRNO: {
      *(int*)pArg = ((unixFile*)id)->lastErrno;
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_CHUNK_SIZE: {
      ((unixFile*)id)->szChunk = *(int *)pArg;
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_SIZE_HINT: {
      return fcntlSizeHint((unixFile *)id, *(i64 *)pArg);
    }
#ifndef NDEBUG
    /* The pager calls this method to signal that it has done
    ** a rollback and that the database is therefore unchanged and
    ** it hence it is OK for the transaction change counter to be
    ** unchanged.
    */
    case SQLITE_FCNTL_DB_UNCHANGED: {
      ((unixFile*)id)->dbUpdate = 0;
      return SQLITE_OK;
    }
#endif
#if SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__)
    case SQLITE_SET_LOCKPROXYFILE:
    case SQLITE_GET_LOCKPROXYFILE: {
      return proxyFileControl(id,op,pArg);
    }
#endif /* SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__) */
    case SQLITE_FCNTL_SYNC_OMITTED: {
      return SQLITE_OK;  /* A no-op */
    }
  }
  return SQLITE_NOTFOUND;
}