#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_10__ {scalar_t__ bEof; int /*<<< orphan*/  iStartOff; int /*<<< orphan*/ * aFile; int /*<<< orphan*/  pTask; } ;
struct TYPE_9__ {scalar_t__ iReadOff; scalar_t__ iEof; int nKey; int /*<<< orphan*/  aKey; TYPE_2__* pIncr; } ;
typedef  TYPE_1__ PmaReader ;
typedef  TYPE_2__ IncrMerger ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  testcase (int) ; 
 int vdbeIncrSwap (TYPE_2__*) ; 
 int vdbePmaReadBlob (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int vdbePmaReadVarint (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  vdbePmaReaderClear (TYPE_1__*) ; 
 int vdbePmaReaderSeek (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdbePmaReaderNext(PmaReader *pReadr){
  int rc = SQLITE_OK;             /* Return Code */
  u64 nRec = 0;                   /* Size of record in bytes */


  if( pReadr->iReadOff>=pReadr->iEof ){
    IncrMerger *pIncr = pReadr->pIncr;
    int bEof = 1;
    if( pIncr ){
      rc = vdbeIncrSwap(pIncr);
      if( rc==SQLITE_OK && pIncr->bEof==0 ){
        rc = vdbePmaReaderSeek(
            pIncr->pTask, pReadr, &pIncr->aFile[0], pIncr->iStartOff
        );
        bEof = 0;
      }
    }

    if( bEof ){
      /* This is an EOF condition */
      vdbePmaReaderClear(pReadr);
      testcase( rc!=SQLITE_OK );
      return rc;
    }
  }

  if( rc==SQLITE_OK ){
    rc = vdbePmaReadVarint(pReadr, &nRec);
  }
  if( rc==SQLITE_OK ){
    pReadr->nKey = (int)nRec;
    rc = vdbePmaReadBlob(pReadr, (int)nRec, &pReadr->aKey);
    testcase( rc!=SQLITE_OK );
  }

  return rc;
}