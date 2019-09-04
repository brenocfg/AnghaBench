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
struct TYPE_3__ {scalar_t__ lastErrno; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int SQLITE_IOERR_READ ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int seekAndRead (TYPE_1__*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int unixRead(
  sqlite3_file *id, 
  void *pBuf, 
  int amt,
  sqlite3_int64 offset
){
  unixFile *pFile = (unixFile *)id;
  int got;
  assert( id );

  /* If this is a database file (not a journal, master-journal or temp
  ** file), the bytes in the locking range should never be read or written. */
#if 0
  assert( pFile->pUnused==0
       || offset>=PENDING_BYTE+512
       || offset+amt<=PENDING_BYTE 
  );
#endif

  got = seekAndRead(pFile, offset, pBuf, amt);
  if( got==amt ){
    return SQLITE_OK;
  }else if( got<0 ){
    /* lastErrno set by seekAndRead */
    return SQLITE_IOERR_READ;
  }else{
    pFile->lastErrno = 0; /* not a system error */
    /* Unread parts of the buffer must be zero-filled */
    memset(&((char*)pBuf)[got], 0, amt-got);
    return SQLITE_IOERR_SHORT_READ;
  }
}