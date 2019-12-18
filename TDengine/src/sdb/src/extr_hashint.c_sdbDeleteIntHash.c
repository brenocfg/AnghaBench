#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ maxSessions; int /*<<< orphan*/  longHashMemPool; TYPE_2__** longHashList; } ;
struct TYPE_6__ {scalar_t__ key; TYPE_1__* prev; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* next; } ;
typedef  TYPE_2__ SLongHash ;
typedef  TYPE_3__ SHashObj ;

/* Variables and functions */
 int sdbHashLong (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  taosMemPoolFree (int /*<<< orphan*/ ,char*) ; 

void sdbDeleteIntHash(void *handle, void *pKey) {
  int        hash;
  SLongHash *pNode;
  SHashObj * pObj;
  uint32_t   key = *((uint32_t *)pKey);

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return;

  hash = sdbHashLong(pObj, key);

  pNode = pObj->longHashList[hash];
  while (pNode) {
    if (pNode->key == key) break;

    pNode = pNode->next;
  }

  if (pNode) {
    if (pNode->prev) {
      pNode->prev->next = pNode->next;
    } else {
      pObj->longHashList[hash] = pNode->next;
    }

    if (pNode->next) {
      pNode->next->prev = pNode->prev;
    }

    taosMemPoolFree(pObj->longHashMemPool, (char *)pNode);
  }
}