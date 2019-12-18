#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  scalar_t__ i64 ;
struct TYPE_9__ {scalar_t__ zChunk; struct TYPE_9__* pNext; } ;
struct TYPE_7__ {scalar_t__ iOffset; } ;
struct TYPE_8__ {int nChunkSize; TYPE_1__ endpoint; TYPE_3__* pFirst; int /*<<< orphan*/  flags; int /*<<< orphan*/  zJournal; int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_2__ MemJournal ;
typedef  TYPE_3__ FileChunk ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  memjrnlFreeChunks (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ *) ; 
 int sqlite3OsOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static int memjrnlCreateFile(MemJournal *p){
  int rc;
  sqlite3_file *pReal = (sqlite3_file*)p;
  MemJournal copy = *p;

  memset(p, 0, sizeof(MemJournal));
  rc = sqlite3OsOpen(copy.pVfs, copy.zJournal, pReal, copy.flags, 0);
  if( rc==SQLITE_OK ){
    int nChunk = copy.nChunkSize;
    i64 iOff = 0;
    FileChunk *pIter;
    for(pIter=copy.pFirst; pIter; pIter=pIter->pNext){
      if( iOff + nChunk > copy.endpoint.iOffset ){
        nChunk = copy.endpoint.iOffset - iOff;
      }
      rc = sqlite3OsWrite(pReal, (u8*)pIter->zChunk, nChunk, iOff);
      if( rc ) break;
      iOff += nChunk;
    }
    if( rc==SQLITE_OK ){
      /* No error has occurred. Free the in-memory buffers. */
      memjrnlFreeChunks(&copy);
    }
  }
  if( rc!=SQLITE_OK ){
    /* If an error occurred while creating or writing to the file, restore
    ** the original before returning. This way, SQLite uses the in-memory
    ** journal data to roll back changes made to the internal page-cache
    ** before this function was called.  */
    sqlite3OsClose(pReal);
    *p = copy;
  }
  return rc;
}