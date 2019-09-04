#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dbUpdate; int transCntrChng; scalar_t__ lastErrno; scalar_t__ inNormalWrite; } ;
typedef  TYPE_1__ unixFile ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 int SQLITE_FULL ; 
 int SQLITE_IOERR_WRITE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SimulateDiskfullError (int) ; 
 int /*<<< orphan*/  SimulateIOError (int) ; 
 int /*<<< orphan*/  SimulateIOErrorBenign (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int seekAndRead (TYPE_1__*,int,char*,int) ; 
 int seekAndWrite (TYPE_1__*,int,void const*,int) ; 

__attribute__((used)) static int unixWrite(
  sqlite3_file *id, 
  const void *pBuf, 
  int amt,
  sqlite3_int64 offset 
){
  unixFile *pFile = (unixFile*)id;
  int wrote = 0;
  assert( id );
  assert( amt>0 );

  /* If this is a database file (not a journal, master-journal or temp
  ** file), the bytes in the locking range should never be read or written. */
#if 0
  assert( pFile->pUnused==0
       || offset>=PENDING_BYTE+512
       || offset+amt<=PENDING_BYTE 
  );
#endif

#ifndef NDEBUG
  /* If we are doing a normal write to a database file (as opposed to
  ** doing a hot-journal rollback or a write to some file other than a
  ** normal database file) then record the fact that the database
  ** has changed.  If the transaction counter is modified, record that
  ** fact too.
  */
  if( pFile->inNormalWrite ){
    pFile->dbUpdate = 1;  /* The database has been modified */
    if( offset<=24 && offset+amt>=27 ){
      int rc;
      char oldCntr[4];
      SimulateIOErrorBenign(1);
      rc = seekAndRead(pFile, 24, oldCntr, 4);
      SimulateIOErrorBenign(0);
      if( rc!=4 || memcmp(oldCntr, &((char*)pBuf)[24-offset], 4)!=0 ){
        pFile->transCntrChng = 1;  /* The transaction counter has changed */
      }
    }
  }
#endif

  while( amt>0 && (wrote = seekAndWrite(pFile, offset, pBuf, amt))>0 ){
    amt -= wrote;
    offset += wrote;
    pBuf = &((char*)pBuf)[wrote];
  }
  SimulateIOError(( wrote=(-1), amt=1 ));
  SimulateDiskfullError(( wrote=0, amt=1 ));

  if( amt>0 ){
    if( wrote<0 && pFile->lastErrno!=ENOSPC ){
      /* lastErrno set by seekAndWrite */
      return SQLITE_IOERR_WRITE;
    }else{
      pFile->lastErrno = 0; /* not a system error */
      return SQLITE_FULL;
    }
  }

  return SQLITE_OK;
}