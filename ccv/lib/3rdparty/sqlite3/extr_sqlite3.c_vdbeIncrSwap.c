#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ iStartOff; int bEof; TYPE_1__* aFile; int /*<<< orphan*/  pTask; scalar_t__ bUseThread; } ;
struct TYPE_6__ {scalar_t__ iEof; } ;
typedef  TYPE_1__ SorterFile ;
typedef  TYPE_2__ IncrMerger ;

/* Variables and functions */
 int SQLITE_OK ; 
 int vdbeIncrBgPopulate (TYPE_2__*) ; 
 int vdbeIncrPopulate (TYPE_2__*) ; 
 int vdbeSorterJoinThread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdbeIncrSwap(IncrMerger *pIncr){
  int rc = SQLITE_OK;

#if SQLITE_MAX_WORKER_THREADS>0
  if( pIncr->bUseThread ){
    rc = vdbeSorterJoinThread(pIncr->pTask);

    if( rc==SQLITE_OK ){
      SorterFile f0 = pIncr->aFile[0];
      pIncr->aFile[0] = pIncr->aFile[1];
      pIncr->aFile[1] = f0;
    }

    if( rc==SQLITE_OK ){
      if( pIncr->aFile[0].iEof==pIncr->iStartOff ){
        pIncr->bEof = 1;
      }else{
        rc = vdbeIncrBgPopulate(pIncr);
      }
    }
  }else
#endif
  {
    rc = vdbeIncrPopulate(pIncr);
    pIncr->aFile[0] = pIncr->aFile[1];
    if( pIncr->aFile[0].iEof==pIncr->iStartOff ){
      pIncr->bEof = 1;
    }
  }

  return rc;
}