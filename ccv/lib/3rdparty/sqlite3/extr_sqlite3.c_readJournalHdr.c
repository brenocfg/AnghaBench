#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  aMagic ;
struct TYPE_6__ {scalar_t__ journalOff; scalar_t__ journalHdr; int cksumInit; int pageSize; int sectorSize; int /*<<< orphan*/  jfd; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ JOURNAL_HDR_SZ (TYPE_1__*) ; 
 int MAX_SECTOR_SIZE ; 
 int SQLITE_DONE ; 
 int SQLITE_MAX_PAGE_SIZE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  aJournalMagic ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isOpen (int /*<<< orphan*/ ) ; 
 scalar_t__ journalHdrOffset (TYPE_1__*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int read32bits (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,unsigned char*,int,scalar_t__) ; 
 int sqlite3PagerSetPagesize (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int readJournalHdr(
  Pager *pPager,               /* Pager object */
  int isHot,
  i64 journalSize,             /* Size of the open journal file in bytes */
  u32 *pNRec,                  /* OUT: Value read from the nRec field */
  u32 *pDbSize                 /* OUT: Value of original database size field */
){
  int rc;                      /* Return code */
  unsigned char aMagic[8];     /* A buffer to hold the magic header */
  i64 iHdrOff;                 /* Offset of journal header being read */

  assert( isOpen(pPager->jfd) );      /* Journal file must be open. */

  /* Advance Pager.journalOff to the start of the next sector. If the
  ** journal file is too small for there to be a header stored at this
  ** point, return SQLITE_DONE.
  */
  pPager->journalOff = journalHdrOffset(pPager);
  if( pPager->journalOff+JOURNAL_HDR_SZ(pPager) > journalSize ){
    return SQLITE_DONE;
  }
  iHdrOff = pPager->journalOff;

  /* Read in the first 8 bytes of the journal header. If they do not match
  ** the  magic string found at the start of each journal header, return
  ** SQLITE_DONE. If an IO error occurs, return an error code. Otherwise,
  ** proceed.
  */
  if( isHot || iHdrOff!=pPager->journalHdr ){
    rc = sqlite3OsRead(pPager->jfd, aMagic, sizeof(aMagic), iHdrOff);
    if( rc ){
      return rc;
    }
    if( memcmp(aMagic, aJournalMagic, sizeof(aMagic))!=0 ){
      return SQLITE_DONE;
    }
  }

  /* Read the first three 32-bit fields of the journal header: The nRec
  ** field, the checksum-initializer and the database size at the start
  ** of the transaction. Return an error code if anything goes wrong.
  */
  if( SQLITE_OK!=(rc = read32bits(pPager->jfd, iHdrOff+8, pNRec))
   || SQLITE_OK!=(rc = read32bits(pPager->jfd, iHdrOff+12, &pPager->cksumInit))
   || SQLITE_OK!=(rc = read32bits(pPager->jfd, iHdrOff+16, pDbSize))
  ){
    return rc;
  }

  if( pPager->journalOff==0 ){
    u32 iPageSize;               /* Page-size field of journal header */
    u32 iSectorSize;             /* Sector-size field of journal header */

    /* Read the page-size and sector-size journal header fields. */
    if( SQLITE_OK!=(rc = read32bits(pPager->jfd, iHdrOff+20, &iSectorSize))
     || SQLITE_OK!=(rc = read32bits(pPager->jfd, iHdrOff+24, &iPageSize))
    ){
      return rc;
    }

    /* Versions of SQLite prior to 3.5.8 set the page-size field of the
    ** journal header to zero. In this case, assume that the Pager.pageSize
    ** variable is already set to the correct page size.
    */
    if( iPageSize==0 ){
      iPageSize = pPager->pageSize;
    }

    /* Check that the values read from the page-size and sector-size fields
    ** are within range. To be 'in range', both values need to be a power
    ** of two greater than or equal to 512 or 32, and not greater than their 
    ** respective compile time maximum limits.
    */
    if( iPageSize<512                  || iSectorSize<32
     || iPageSize>SQLITE_MAX_PAGE_SIZE || iSectorSize>MAX_SECTOR_SIZE
     || ((iPageSize-1)&iPageSize)!=0   || ((iSectorSize-1)&iSectorSize)!=0 
    ){
      /* If the either the page-size or sector-size in the journal-header is 
      ** invalid, then the process that wrote the journal-header must have 
      ** crashed before the header was synced. In this case stop reading 
      ** the journal file here.
      */
      return SQLITE_DONE;
    }

    /* Update the page-size to match the value read from the journal. 
    ** Use a testcase() macro to make sure that malloc failure within 
    ** PagerSetPagesize() is tested.
    */
    rc = sqlite3PagerSetPagesize(pPager, &iPageSize, -1);
    testcase( rc!=SQLITE_OK );

    /* Update the assumed sector-size to match the value used by 
    ** the process that created this journal. If this journal was
    ** created by a process other than this one, then this routine
    ** is being called from within pager_playback(). The local value
    ** of Pager.sectorSize is restored at the end of that routine.
    */
    pPager->sectorSize = iSectorSize;
  }

  pPager->journalOff += JOURNAL_HDR_SZ(pPager);
  return rc;
}