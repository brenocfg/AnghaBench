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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ maxSessions; int /*<<< orphan*/  ipHashMemPool; TYPE_2__** ipHashList; } ;
struct TYPE_6__ {short port; TYPE_1__* prev; struct TYPE_6__* next; int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {TYPE_2__* next; } ;
typedef  TYPE_2__ SIpHash ;
typedef  TYPE_3__ SHashObj ;

/* Variables and functions */
 int taosHashIp (TYPE_3__*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  taosMemPoolFree (int /*<<< orphan*/ ,char*) ; 

void taosDeleteIpHash(void *handle, uint32_t ip, short port) {
  int       hash;
  SIpHash * pNode;
  SHashObj *pObj;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return;

  hash = taosHashIp(pObj, ip, port);

  pNode = pObj->ipHashList[hash];
  while (pNode) {
    if (pNode->ip == ip && pNode->port == port) break;

    pNode = pNode->next;
  }

  if (pNode) {
    if (pNode->prev) {
      pNode->prev->next = pNode->next;
    } else {
      pObj->ipHashList[hash] = pNode->next;
    }

    if (pNode->next) {
      pNode->next->prev = pNode->prev;
    }

    taosMemPoolFree(pObj->ipHashMemPool, (char *)pNode);
  }
}