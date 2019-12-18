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
struct TYPE_4__ {scalar_t__ journalMode; int /*<<< orphan*/  sjfd; scalar_t__ subjInMemory; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_JOURNALMODE_MEMORY ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_OPEN_SUBJOURNAL ; 
 int /*<<< orphan*/  isOpen (int /*<<< orphan*/ ) ; 
 int pagerOpentemp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3MemJournalOpen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int openSubJournal(Pager *pPager){
  int rc = SQLITE_OK;
  if( !isOpen(pPager->sjfd) ){
    if( pPager->journalMode==PAGER_JOURNALMODE_MEMORY || pPager->subjInMemory ){
      sqlite3MemJournalOpen(pPager->sjfd);
    }else{
      rc = pagerOpentemp(pPager, pPager->sjfd, SQLITE_OPEN_SUBJOURNAL);
    }
  }
  return rc;
}