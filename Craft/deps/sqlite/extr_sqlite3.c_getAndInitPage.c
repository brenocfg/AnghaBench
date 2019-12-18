#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  scalar_t__ Pgno ;
typedef  int /*<<< orphan*/  MemPage ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int SQLITE_CORRUPT ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeGetPage (TYPE_1__*,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int btreeInitPage (int /*<<< orphan*/ *) ; 
 scalar_t__ btreePagecount (TYPE_1__*) ; 
 int /*<<< orphan*/  releasePage (int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int getAndInitPage(
  BtShared *pBt,                  /* The database file */
  Pgno pgno,                      /* Number of the page to get */
  MemPage **ppPage,               /* Write the page pointer here */
  int bReadonly                   /* True if a read-only (mmap) page is ok */
){
  int rc;
  assert( sqlite3_mutex_held(pBt->mutex) );

  if( pgno>btreePagecount(pBt) ){
    rc = SQLITE_CORRUPT_BKPT;
  }else{
    rc = btreeGetPage(pBt, pgno, ppPage, 0, bReadonly);
    if( rc==SQLITE_OK ){
      rc = btreeInitPage(*ppPage);
      if( rc!=SQLITE_OK ){
        releasePage(*ppPage);
      }
    }
  }

  testcase( pgno==0 );
  assert( pgno!=0 || rc==SQLITE_CORRUPT );
  return rc;
}