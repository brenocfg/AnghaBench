#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int aData; } ;
struct TYPE_4__ {scalar_t__ pCursor; scalar_t__ inTransaction; TYPE_3__* pPage1; int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 scalar_t__ TRANS_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  releasePage (TYPE_3__*) ; 
 int sqlite3PagerRefcount (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlockBtreeIfUnused(BtShared *pBt){
  assert( sqlite3_mutex_held(pBt->mutex) );
  assert( pBt->pCursor==0 || pBt->inTransaction>TRANS_NONE );
  if( pBt->inTransaction==TRANS_NONE && pBt->pPage1!=0 ){
    assert( pBt->pPage1->aData );
    assert( sqlite3PagerRefcount(pBt->pPager)==1 );
    assert( pBt->pPage1->aData );
    releasePage(pBt->pPage1);
    pBt->pPage1 = 0;
  }
}