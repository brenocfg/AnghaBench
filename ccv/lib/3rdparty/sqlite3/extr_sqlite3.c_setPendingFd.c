#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* pUnused; } ;
typedef  TYPE_1__ unixInodeInfo ;
struct TYPE_6__ {int h; TYPE_3__* pPreallocatedUnused; TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixFile ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_3__ UnixUnusedFd ;

/* Variables and functions */
 int /*<<< orphan*/  nUnusedFd ; 

__attribute__((used)) static void setPendingFd(unixFile *pFile){
  unixInodeInfo *pInode = pFile->pInode;
  UnixUnusedFd *p = pFile->pPreallocatedUnused;
  p->pNext = pInode->pUnused;
  pInode->pUnused = p;
  pFile->h = -1;
  pFile->pPreallocatedUnused = 0;
  nUnusedFd++;
}