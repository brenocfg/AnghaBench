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
struct TYPE_4__ {int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  int /*<<< orphan*/  MemPage ;
typedef  int /*<<< orphan*/  DbPage ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int PAGER_ACQUIRE_NOCONTENT ; 
 int PAGER_ACQUIRE_READONLY ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * btreePageFromDbPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sqlite3PagerAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btreeGetPage(
  BtShared *pBt,       /* The btree */
  Pgno pgno,           /* Number of the page to fetch */
  MemPage **ppPage,    /* Return the page in this parameter */
  int noContent,       /* Do not load page content if true */
  int bReadonly        /* True if a read-only (mmap) page is ok */
){
  int rc;
  DbPage *pDbPage;
  int flags = (noContent ? PAGER_ACQUIRE_NOCONTENT : 0) 
            | (bReadonly ? PAGER_ACQUIRE_READONLY : 0);

  assert( noContent==0 || bReadonly==0 );
  assert( sqlite3_mutex_held(pBt->mutex) );
  rc = sqlite3PagerAcquire(pBt->pPager, pgno, (DbPage**)&pDbPage, flags);
  if( rc ) return rc;
  *ppPage = btreePageFromDbPage(pDbPage, pgno, pBt);
  return SQLITE_OK;
}