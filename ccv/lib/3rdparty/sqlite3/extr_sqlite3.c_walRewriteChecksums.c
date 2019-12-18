#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int i64 ;
typedef  int /*<<< orphan*/  aFrame ;
struct TYPE_5__ {void** aFrameCksum; } ;
struct TYPE_6__ {int szPage; int iReCksum; int /*<<< orphan*/  pWalFd; TYPE_1__ hdr; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int WAL_FRAME_HDRSIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* sqlite3Get4byte (int /*<<< orphan*/ *) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const,int) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_malloc (int const) ; 
 int /*<<< orphan*/  walEncodeFrame (TYPE_2__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int walFrameOffset (int,int const) ; 

__attribute__((used)) static int walRewriteChecksums(Wal *pWal, u32 iLast){
  const int szPage = pWal->szPage;/* Database page size */
  int rc = SQLITE_OK;             /* Return code */
  u8 *aBuf;                       /* Buffer to load data from wal file into */
  u8 aFrame[WAL_FRAME_HDRSIZE];   /* Buffer to assemble frame-headers in */
  u32 iRead;                      /* Next frame to read from wal file */
  i64 iCksumOff;

  aBuf = sqlite3_malloc(szPage + WAL_FRAME_HDRSIZE);
  if( aBuf==0 ) return SQLITE_NOMEM_BKPT;

  /* Find the checksum values to use as input for the recalculating the
  ** first checksum. If the first frame is frame 1 (implying that the current
  ** transaction restarted the wal file), these values must be read from the
  ** wal-file header. Otherwise, read them from the frame header of the
  ** previous frame.  */
  assert( pWal->iReCksum>0 );
  if( pWal->iReCksum==1 ){
    iCksumOff = 24;
  }else{
    iCksumOff = walFrameOffset(pWal->iReCksum-1, szPage) + 16;
  }
  rc = sqlite3OsRead(pWal->pWalFd, aBuf, sizeof(u32)*2, iCksumOff);
  pWal->hdr.aFrameCksum[0] = sqlite3Get4byte(aBuf);
  pWal->hdr.aFrameCksum[1] = sqlite3Get4byte(&aBuf[sizeof(u32)]);

  iRead = pWal->iReCksum;
  pWal->iReCksum = 0;
  for(; rc==SQLITE_OK && iRead<=iLast; iRead++){
    i64 iOff = walFrameOffset(iRead, szPage);
    rc = sqlite3OsRead(pWal->pWalFd, aBuf, szPage+WAL_FRAME_HDRSIZE, iOff);
    if( rc==SQLITE_OK ){
      u32 iPgno, nDbSize;
      iPgno = sqlite3Get4byte(aBuf);
      nDbSize = sqlite3Get4byte(&aBuf[4]);

      walEncodeFrame(pWal, iPgno, nDbSize, &aBuf[WAL_FRAME_HDRSIZE], aFrame);
      rc = sqlite3OsWrite(pWal->pWalFd, aFrame, sizeof(aFrame), iOff);
    }
  }

  sqlite3_free(aBuf);
  return rc;
}