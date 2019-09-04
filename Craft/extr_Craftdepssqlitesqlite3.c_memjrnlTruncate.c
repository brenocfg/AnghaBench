#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_5__ {struct TYPE_5__* pNext; } ;
struct TYPE_4__ {TYPE_2__* pFirst; } ;
typedef  TYPE_1__ MemJournal ;
typedef  TYPE_2__ FileChunk ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3MemJournalOpen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static int memjrnlTruncate(sqlite3_file *pJfd, sqlite_int64 size){
  MemJournal *p = (MemJournal *)pJfd;
  FileChunk *pChunk;
  assert(size==0);
  UNUSED_PARAMETER(size);
  pChunk = p->pFirst;
  while( pChunk ){
    FileChunk *pTmp = pChunk;
    pChunk = pChunk->pNext;
    sqlite3_free(pTmp);
  }
  sqlite3MemJournalOpen(pJfd);
  return SQLITE_OK;
}