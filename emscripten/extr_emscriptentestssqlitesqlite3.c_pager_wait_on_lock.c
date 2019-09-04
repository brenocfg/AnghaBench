#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int eLock; int /*<<< orphan*/  pBusyHandlerArg; scalar_t__ (* xBusyHandler ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int EXCLUSIVE_LOCK ; 
 int NO_LOCK ; 
 int RESERVED_LOCK ; 
 int SHARED_LOCK ; 
 int SQLITE_BUSY ; 
 int /*<<< orphan*/  assert (int) ; 
 int pagerLockDb (TYPE_1__*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pager_wait_on_lock(Pager *pPager, int locktype){
  int rc;                              /* Return code */

  /* Check that this is either a no-op (because the requested lock is 
  ** already held, or one of the transistions that the busy-handler
  ** may be invoked during, according to the comment above
  ** sqlite3PagerSetBusyhandler().
  */
  assert( (pPager->eLock>=locktype)
       || (pPager->eLock==NO_LOCK && locktype==SHARED_LOCK)
       || (pPager->eLock==RESERVED_LOCK && locktype==EXCLUSIVE_LOCK)
  );

  do {
    rc = pagerLockDb(pPager, locktype);
  }while( rc==SQLITE_BUSY && pPager->xBusyHandler(pPager->pBusyHandlerArg) );
  return rc;
}