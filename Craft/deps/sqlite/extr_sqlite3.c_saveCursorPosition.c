#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ eState; scalar_t__ pKey; TYPE_1__** apPage; scalar_t__ nKey; } ;
struct TYPE_9__ {scalar_t__ intKey; } ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_REQUIRESEEK ; 
 scalar_t__ CURSOR_VALID ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeReleaseAllCursorPages (TYPE_2__*) ; 
 int cursorHoldsMutex (TYPE_2__*) ; 
 int /*<<< orphan*/  invalidateOverflowCache (TYPE_2__*) ; 
 int sqlite3BtreeKey (TYPE_2__*,int /*<<< orphan*/ ,int,void*) ; 
 int sqlite3BtreeKeySize (TYPE_2__*,scalar_t__*) ; 
 void* sqlite3Malloc (int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 

__attribute__((used)) static int saveCursorPosition(BtCursor *pCur){
  int rc;

  assert( CURSOR_VALID==pCur->eState );
  assert( 0==pCur->pKey );
  assert( cursorHoldsMutex(pCur) );

  rc = sqlite3BtreeKeySize(pCur, &pCur->nKey);
  assert( rc==SQLITE_OK );  /* KeySize() cannot fail */

  /* If this is an intKey table, then the above call to BtreeKeySize()
  ** stores the integer key in pCur->nKey. In this case this value is
  ** all that is required. Otherwise, if pCur is not open on an intKey
  ** table, then malloc space for and store the pCur->nKey bytes of key 
  ** data.
  */
  if( 0==pCur->apPage[0]->intKey ){
    void *pKey = sqlite3Malloc( (int)pCur->nKey );
    if( pKey ){
      rc = sqlite3BtreeKey(pCur, 0, (int)pCur->nKey, pKey);
      if( rc==SQLITE_OK ){
        pCur->pKey = pKey;
      }else{
        sqlite3_free(pKey);
      }
    }else{
      rc = SQLITE_NOMEM;
    }
  }
  assert( !pCur->apPage[0]->intKey || !pCur->pKey );

  if( rc==SQLITE_OK ){
    btreeReleaseAllCursorPages(pCur);
    pCur->eState = CURSOR_REQUIRESEEK;
  }

  invalidateOverflowCache(pCur);
  return rc;
}