#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
struct TYPE_5__ {TYPE_2__* pFirst; } ;
typedef  TYPE_1__ MemJournal ;
typedef  TYPE_2__ FileChunk ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void memjrnlFreeChunks(MemJournal *p){
  FileChunk *pIter;
  FileChunk *pNext;
  for(pIter=p->pFirst; pIter; pIter=pNext){
    pNext = pIter->pNext;
    sqlite3_free(pIter);
  } 
  p->pFirst = 0;
}