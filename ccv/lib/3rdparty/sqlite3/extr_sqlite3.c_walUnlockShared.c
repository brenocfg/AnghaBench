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
struct TYPE_3__ {int /*<<< orphan*/  pDbFd; scalar_t__ exclusiveMode; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int SQLITE_SHM_SHARED ; 
 int SQLITE_SHM_UNLOCK ; 
 int /*<<< orphan*/  WALTRACE (char*) ; 
 int /*<<< orphan*/  sqlite3OsShmLock (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  walLockName (int) ; 

__attribute__((used)) static void walUnlockShared(Wal *pWal, int lockIdx){
  if( pWal->exclusiveMode ) return;
  (void)sqlite3OsShmLock(pWal->pDbFd, lockIdx, 1,
                         SQLITE_SHM_UNLOCK | SQLITE_SHM_SHARED);
  WALTRACE(("WAL%p: release SHARED-%s\n", pWal, walLockName(lockIdx)));
}