#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_6__* pList; } ;
struct TYPE_9__ {TYPE_2__ list; TYPE_1__* pMerger; TYPE_4__* pReader; scalar_t__ bUseThreads; scalar_t__ bUsePMA; } ;
typedef  TYPE_3__ VdbeSorter ;
struct TYPE_11__ {int nVal; } ;
struct TYPE_10__ {int nKey; void* aKey; } ;
struct TYPE_7__ {size_t* aTree; TYPE_4__* aReadr; } ;
typedef  TYPE_4__ PmaReader ;

/* Variables and functions */
 void* SRVAL (TYPE_6__*) ; 

__attribute__((used)) static void *vdbeSorterRowkey(
  const VdbeSorter *pSorter,      /* Sorter object */
  int *pnKey                      /* OUT: Size of current key in bytes */
){
  void *pKey;
  if( pSorter->bUsePMA ){
    PmaReader *pReader;
#if SQLITE_MAX_WORKER_THREADS>0
    if( pSorter->bUseThreads ){
      pReader = pSorter->pReader;
    }else
#endif
    /*if( !pSorter->bUseThreads )*/{
      pReader = &pSorter->pMerger->aReadr[pSorter->pMerger->aTree[1]];
    }
    *pnKey = pReader->nKey;
    pKey = pReader->aKey;
  }else{
    *pnKey = pSorter->list.pList->nVal;
    pKey = SRVAL(pSorter->list.pList);
  }
  return pKey;
}