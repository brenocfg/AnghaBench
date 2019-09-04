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
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_mutex ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MUTEX_STATIC_MASTER ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * sqlite3MutexAlloc (int /*<<< orphan*/ ) ; 
 int sqlite3_initialize () ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ *) ; 
 TYPE_1__* vfsList ; 
 int /*<<< orphan*/  vfsUnlink (TYPE_1__*) ; 

int sqlite3_vfs_register(sqlite3_vfs *pVfs, int makeDflt){
  sqlite3_mutex *mutex = 0;
#ifndef SQLITE_OMIT_AUTOINIT
  int rc = sqlite3_initialize();
  if( rc ) return rc;
#endif
  mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
  sqlite3_mutex_enter(mutex);
  vfsUnlink(pVfs);
  if( makeDflt || vfsList==0 ){
    pVfs->pNext = vfsList;
    vfsList = pVfs;
  }else{
    pVfs->pNext = vfsList->pNext;
    vfsList->pNext = pVfs;
  }
  assert(vfsList);
  sqlite3_mutex_leave(mutex);
  return SQLITE_OK;
}