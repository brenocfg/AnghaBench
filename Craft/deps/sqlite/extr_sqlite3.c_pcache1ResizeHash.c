#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {int nHash; TYPE_1__** apHash; TYPE_5__* pGroup; } ;
struct TYPE_7__ {unsigned int iKey; struct TYPE_7__* pNext; } ;
typedef  TYPE_1__ PgHdr1 ;
typedef  TYPE_2__ PCache1 ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcache1EnterMutex (TYPE_5__*) ; 
 int /*<<< orphan*/  pcache1LeaveMutex (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 scalar_t__ sqlite3MallocZero (int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__**) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcache1ResizeHash(PCache1 *p){
  PgHdr1 **apNew;
  unsigned int nNew;
  unsigned int i;

  assert( sqlite3_mutex_held(p->pGroup->mutex) );

  nNew = p->nHash*2;
  if( nNew<256 ){
    nNew = 256;
  }

  pcache1LeaveMutex(p->pGroup);
  if( p->nHash ){ sqlite3BeginBenignMalloc(); }
  apNew = (PgHdr1 **)sqlite3MallocZero(sizeof(PgHdr1 *)*nNew);
  if( p->nHash ){ sqlite3EndBenignMalloc(); }
  pcache1EnterMutex(p->pGroup);
  if( apNew ){
    for(i=0; i<p->nHash; i++){
      PgHdr1 *pPage;
      PgHdr1 *pNext = p->apHash[i];
      while( (pPage = pNext)!=0 ){
        unsigned int h = pPage->iKey % nNew;
        pNext = pPage->pNext;
        pPage->pNext = apNew[h];
        apNew[h] = pPage;
      }
    }
    sqlite3_free(p->apHash);
    p->apHash = apNew;
    p->nHash = nNew;
  }

  return (p->apHash ? SQLITE_OK : SQLITE_NOMEM);
}