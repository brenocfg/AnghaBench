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
struct RowSetEntry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pEntry; scalar_t__ pTree; int /*<<< orphan*/  isSorted; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 int /*<<< orphan*/  rowSetMerge (int /*<<< orphan*/ ,struct RowSetEntry*) ; 
 int /*<<< orphan*/  rowSetSort (TYPE_1__*) ; 
 int /*<<< orphan*/  rowSetTreeToList (scalar_t__,struct RowSetEntry**,struct RowSetEntry**) ; 

__attribute__((used)) static void rowSetToList(RowSet *p){
  if( !p->isSorted ){
    rowSetSort(p);
  }
  if( p->pTree ){
    struct RowSetEntry *pHead, *pTail;
    rowSetTreeToList(p->pTree, &pHead, &pTail);
    p->pTree = 0;
    p->pEntry = rowSetMerge(p->pEntry, pHead);
  }
}