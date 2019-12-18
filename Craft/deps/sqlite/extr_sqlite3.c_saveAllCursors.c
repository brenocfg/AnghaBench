#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pgnoRoot; scalar_t__ eState; scalar_t__ iPage; struct TYPE_8__* pNext; TYPE_1__* pBt; } ;
struct TYPE_7__ {TYPE_2__* pCursor; int /*<<< orphan*/  mutex; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ BtShared ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeReleaseAllCursorPages (TYPE_2__*) ; 
 int saveCursorPosition (TYPE_2__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int saveAllCursors(BtShared *pBt, Pgno iRoot, BtCursor *pExcept){
  BtCursor *p;
  assert( sqlite3_mutex_held(pBt->mutex) );
  assert( pExcept==0 || pExcept->pBt==pBt );
  for(p=pBt->pCursor; p; p=p->pNext){
    if( p!=pExcept && (0==iRoot || p->pgnoRoot==iRoot) ){
      if( p->eState==CURSOR_VALID ){
        int rc = saveCursorPosition(p);
        if( SQLITE_OK!=rc ){
          return rc;
        }
      }else{
        testcase( p->iPage>0 );
        btreeReleaseAllCursorPages(p);
      }
    }
  }
  return SQLITE_OK;
}