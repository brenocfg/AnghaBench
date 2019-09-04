#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RowSetEntry {scalar_t__ pRight; struct RowSetEntry* pLeft; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void rowSetTreeToList(
  struct RowSetEntry *pIn,         /* Root of the input tree */
  struct RowSetEntry **ppFirst,    /* Write head of the output list here */
  struct RowSetEntry **ppLast      /* Write tail of the output list here */
){
  assert( pIn!=0 );
  if( pIn->pLeft ){
    struct RowSetEntry *p;
    rowSetTreeToList(pIn->pLeft, ppFirst, &p);
    p->pRight = pIn;
  }else{
    *ppFirst = pIn;
  }
  if( pIn->pRight ){
    rowSetTreeToList(pIn->pRight, &pIn->pRight, ppLast);
  }else{
    *ppLast = pIn;
  }
  assert( (*ppLast)->pRight==0 );
}