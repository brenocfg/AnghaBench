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
struct TYPE_7__ {TYPE_3__* pUnused; } ;
typedef  TYPE_1__ unixInodeInfo ;
struct TYPE_8__ {TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixFile ;
struct TYPE_9__ {int /*<<< orphan*/  fd; struct TYPE_9__* pNext; } ;
typedef  TYPE_3__ UnixUnusedFd ;

/* Variables and functions */
 int /*<<< orphan*/  nUnusedFd ; 
 int /*<<< orphan*/  robust_close (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 

__attribute__((used)) static void closePendingFds(unixFile *pFile){
  unixInodeInfo *pInode = pFile->pInode;
  UnixUnusedFd *p;
  UnixUnusedFd *pNext;
  for(p=pInode->pUnused; p; p=pNext){
    pNext = p->pNext;
    robust_close(pFile, p->fd, __LINE__);
    sqlite3_free(p);
    nUnusedFd--;
  }
  pInode->pUnused = 0;
}