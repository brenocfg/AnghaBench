#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ keepTimer; int /*<<< orphan*/ ** connHashList; int /*<<< orphan*/  connHashMemPool; int /*<<< orphan*/ * count; int /*<<< orphan*/  total; int /*<<< orphan*/  (* cleanFp ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ time; struct TYPE_6__* next; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  data; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ SConnHash ;
typedef  TYPE_2__ SConnCache ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosMemPoolFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

void taosRemoveExpiredNodes(SConnCache *pObj, SConnHash *pNode, int hash, uint64_t time) {
  if (pNode == NULL) return;
  if (time < pObj->keepTimer + pNode->time) return;

  SConnHash *pPrev = pNode->prev, *pNext;

  while (pNode) {
    (*pObj->cleanFp)(pNode->data);
    pNext = pNode->next;
    pObj->total--;
    pObj->count[hash]--;
    tscTrace("%p ip:0x%x:%d:%d:%p removed, connections in cache:%d", pNode->data, pNode->ip, pNode->port, hash, pNode,
             pObj->count[hash]);
    taosMemPoolFree(pObj->connHashMemPool, (char *)pNode);
    pNode = pNext;
  }

  if (pPrev)
    pPrev->next = NULL;
  else
    pObj->connHashList[hash] = NULL;
}