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
struct RowSetEntry {int dummy; } ;
struct TYPE_5__ {int rsFlags; TYPE_1__* pForest; int /*<<< orphan*/  pEntry; } ;
struct TYPE_4__ {struct TYPE_4__* pRight; struct RowSetEntry* pLeft; } ;
typedef  TYPE_2__ RowSet ;

/* Variables and functions */
 int ROWSET_NEXT ; 
 int ROWSET_SORTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rowSetEntryMerge (int /*<<< orphan*/ ,struct RowSetEntry*) ; 
 int /*<<< orphan*/  rowSetEntrySort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rowSetTreeToList (struct RowSetEntry*,struct RowSetEntry**,struct RowSetEntry**) ; 

__attribute__((used)) static void rowSetToList(RowSet *p){

  /* This routine is called only once */
  assert( p!=0 && (p->rsFlags & ROWSET_NEXT)==0 );

  if( (p->rsFlags & ROWSET_SORTED)==0 ){
    p->pEntry = rowSetEntrySort(p->pEntry);
  }

  /* While this module could theoretically support it, sqlite3RowSetNext()
  ** is never called after sqlite3RowSetText() for the same RowSet.  So
  ** there is never a forest to deal with.  Should this change, simply
  ** remove the assert() and the #if 0. */
  assert( p->pForest==0 );
#if 0
  while( p->pForest ){
    struct RowSetEntry *pTree = p->pForest->pLeft;
    if( pTree ){
      struct RowSetEntry *pHead, *pTail;
      rowSetTreeToList(pTree, &pHead, &pTail);
      p->pEntry = rowSetEntryMerge(p->pEntry, pHead);
    }
    p->pForest = p->pForest->pRight;
  }
#endif
  p->rsFlags |= ROWSET_NEXT;  /* Verify this routine is never called again */
}