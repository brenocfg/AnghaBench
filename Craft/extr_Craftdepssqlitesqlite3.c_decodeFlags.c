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
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  max1bytePayload; int /*<<< orphan*/  minLocal; int /*<<< orphan*/  maxLocal; int /*<<< orphan*/  minLeaf; int /*<<< orphan*/  maxLeaf; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int hdrOffset; int pgno; int leaf; int childPtrSize; int intKey; int hasData; int /*<<< orphan*/  max1bytePayload; int /*<<< orphan*/  minLocal; int /*<<< orphan*/  maxLocal; TYPE_2__* pBt; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int PTF_INTKEY ; 
 int PTF_LEAF ; 
 int PTF_LEAFDATA ; 
 int PTF_ZERODATA ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decodeFlags(MemPage *pPage, int flagByte){
  BtShared *pBt;     /* A copy of pPage->pBt */

  assert( pPage->hdrOffset==(pPage->pgno==1 ? 100 : 0) );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  pPage->leaf = (u8)(flagByte>>3);  assert( PTF_LEAF == 1<<3 );
  flagByte &= ~PTF_LEAF;
  pPage->childPtrSize = 4-4*pPage->leaf;
  pBt = pPage->pBt;
  if( flagByte==(PTF_LEAFDATA | PTF_INTKEY) ){
    pPage->intKey = 1;
    pPage->hasData = pPage->leaf;
    pPage->maxLocal = pBt->maxLeaf;
    pPage->minLocal = pBt->minLeaf;
  }else if( flagByte==PTF_ZERODATA ){
    pPage->intKey = 0;
    pPage->hasData = 0;
    pPage->maxLocal = pBt->maxLocal;
    pPage->minLocal = pBt->minLocal;
  }else{
    return SQLITE_CORRUPT_BKPT;
  }
  pPage->max1bytePayload = pBt->max1bytePayload;
  return SQLITE_OK;
}