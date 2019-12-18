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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int nOverflow; int* aiOvfl; int /*<<< orphan*/ ** apOvfl; TYPE_1__* pBt; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * findCell (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 *findOverflowCell(MemPage *pPage, int iCell){
  int i;
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  for(i=pPage->nOverflow-1; i>=0; i--){
    int k;
    k = pPage->aiOvfl[i];
    if( k<=iCell ){
      if( k==iCell ){
        return pPage->apOvfl[i];
      }
      iCell--;
    }
  }
  return findCell(pPage, iCell);
}