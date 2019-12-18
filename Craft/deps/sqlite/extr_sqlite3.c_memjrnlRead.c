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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ sqlite_int64 ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {int /*<<< orphan*/ * zChunk; struct TYPE_9__* pNext; } ;
struct TYPE_7__ {scalar_t__ iOffset; TYPE_4__* pChunk; } ;
struct TYPE_6__ {scalar_t__ iOffset; } ;
struct TYPE_8__ {TYPE_2__ readpoint; TYPE_4__* pFirst; TYPE_1__ endpoint; } ;
typedef  TYPE_3__ MemJournal ;
typedef  TYPE_4__ FileChunk ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_4__*) ; 
 scalar_t__ JOURNAL_CHUNKSIZE ; 
 int MIN (int,scalar_t__) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int memjrnlRead(
  sqlite3_file *pJfd,    /* The journal file from which to read */
  void *zBuf,            /* Put the results here */
  int iAmt,              /* Number of bytes to read */
  sqlite_int64 iOfst     /* Begin reading at this offset */
){
  MemJournal *p = (MemJournal *)pJfd;
  u8 *zOut = zBuf;
  int nRead = iAmt;
  int iChunkOffset;
  FileChunk *pChunk;

  /* SQLite never tries to read past the end of a rollback journal file */
  assert( iOfst+iAmt<=p->endpoint.iOffset );

  if( p->readpoint.iOffset!=iOfst || iOfst==0 ){
    sqlite3_int64 iOff = 0;
    for(pChunk=p->pFirst; 
        ALWAYS(pChunk) && (iOff+JOURNAL_CHUNKSIZE)<=iOfst;
        pChunk=pChunk->pNext
    ){
      iOff += JOURNAL_CHUNKSIZE;
    }
  }else{
    pChunk = p->readpoint.pChunk;
  }

  iChunkOffset = (int)(iOfst%JOURNAL_CHUNKSIZE);
  do {
    int iSpace = JOURNAL_CHUNKSIZE - iChunkOffset;
    int nCopy = MIN(nRead, (JOURNAL_CHUNKSIZE - iChunkOffset));
    memcpy(zOut, &pChunk->zChunk[iChunkOffset], nCopy);
    zOut += nCopy;
    nRead -= iSpace;
    iChunkOffset = 0;
  } while( nRead>=0 && (pChunk=pChunk->pNext)!=0 && nRead>0 );
  p->readpoint.iOffset = iOfst+iAmt;
  p->readpoint.pChunk = pChunk;

  return SQLITE_OK;
}