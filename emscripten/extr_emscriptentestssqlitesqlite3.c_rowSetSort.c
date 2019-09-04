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
struct RowSetEntry {struct RowSetEntry* pRight; } ;
typedef  int /*<<< orphan*/  aBucket ;
struct TYPE_3__ {int isSorted; scalar_t__ pLast; struct RowSetEntry* pEntry; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct RowSetEntry**,int /*<<< orphan*/ ,int) ; 
 struct RowSetEntry* rowSetMerge (struct RowSetEntry*,struct RowSetEntry*) ; 

__attribute__((used)) static void rowSetSort(RowSet *p){
  unsigned int i;
  struct RowSetEntry *pEntry;
  struct RowSetEntry *aBucket[40];

  assert( p->isSorted==0 );
  memset(aBucket, 0, sizeof(aBucket));
  while( p->pEntry ){
    pEntry = p->pEntry;
    p->pEntry = pEntry->pRight;
    pEntry->pRight = 0;
    for(i=0; aBucket[i]; i++){
      pEntry = rowSetMerge(aBucket[i], pEntry);
      aBucket[i] = 0;
    }
    aBucket[i] = pEntry;
  }
  pEntry = 0;
  for(i=0; i<sizeof(aBucket)/sizeof(aBucket[0]); i++){
    pEntry = rowSetMerge(pEntry, aBucket[i]);
  }
  p->pEntry = pEntry;
  p->pLast = 0;
  p->isSorted = 1;
}