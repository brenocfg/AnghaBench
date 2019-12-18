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
struct TYPE_3__ {scalar_t__ nFetchOut; scalar_t__ mmapSizeActual; scalar_t__ mmapSize; scalar_t__ pMapRegion; } ;
typedef  TYPE_1__ unixFile ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  osMunmap (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void unixUnmapfile(unixFile *pFd){
  assert( pFd->nFetchOut==0 );
#if SQLITE_MAX_MMAP_SIZE>0
  if( pFd->pMapRegion ){
    osMunmap(pFd->pMapRegion, pFd->mmapSizeActual);
    pFd->pMapRegion = 0;
    pFd->mmapSize = 0;
    pFd->mmapSizeActual = 0;
  }
#endif
}