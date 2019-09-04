#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ bigEndCksum; int /*<<< orphan*/  aSalt; scalar_t__* aFrameCksum; } ;
struct TYPE_5__ {int szPage; TYPE_1__ hdr; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 scalar_t__ SQLITE_BIGENDIAN ; 
 int WAL_FRAME_HDRSIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3Get4byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walChecksumBytes (int,int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int walDecodeFrame(
  Wal *pWal,                      /* The write-ahead log */
  u32 *piPage,                    /* OUT: Database page number for frame */
  u32 *pnTruncate,                /* OUT: New db size (or 0 if not commit) */
  u8 *aData,                      /* Pointer to page data (for checksum) */
  u8 *aFrame                      /* Frame data */
){
  int nativeCksum;                /* True for native byte-order checksums */
  u32 *aCksum = pWal->hdr.aFrameCksum;
  u32 pgno;                       /* Page number of the frame */
  assert( WAL_FRAME_HDRSIZE==24 );

  /* A frame is only valid if the salt values in the frame-header
  ** match the salt values in the wal-header. 
  */
  if( memcmp(&pWal->hdr.aSalt, &aFrame[8], 8)!=0 ){
    return 0;
  }

  /* A frame is only valid if the page number is creater than zero.
  */
  pgno = sqlite3Get4byte(&aFrame[0]);
  if( pgno==0 ){
    return 0;
  }

  /* A frame is only valid if a checksum of the WAL header,
  ** all prior frams, the first 16 bytes of this frame-header, 
  ** and the frame-data matches the checksum in the last 8 
  ** bytes of this frame-header.
  */
  nativeCksum = (pWal->hdr.bigEndCksum==SQLITE_BIGENDIAN);
  walChecksumBytes(nativeCksum, aFrame, 8, aCksum, aCksum);
  walChecksumBytes(nativeCksum, aData, pWal->szPage, aCksum, aCksum);
  if( aCksum[0]!=sqlite3Get4byte(&aFrame[16]) 
   || aCksum[1]!=sqlite3Get4byte(&aFrame[20]) 
  ){
    /* Checksum failed. */
    return 0;
  }

  /* If we reach this point, the frame is valid.  Return the page number
  ** and the new database size.
  */
  *piPage = pgno;
  *pnTruncate = sqlite3Get4byte(&aFrame[4]);
  return 1;
}