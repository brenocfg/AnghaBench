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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ maxSessions; TYPE_1__** ipHashList; } ;
struct TYPE_4__ {short port; void* data; struct TYPE_4__* next; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ SIpHash ;
typedef  TYPE_2__ SHashObj ;

/* Variables and functions */
 int taosHashIp (TYPE_2__*,int /*<<< orphan*/ ,short) ; 

void *taosGetIpHash(void *handle, uint32_t ip, short port) {
  int       hash;
  SIpHash * pNode;
  SHashObj *pObj;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return NULL;

  hash = taosHashIp(pObj, ip, port);
  pNode = pObj->ipHashList[hash];

  while (pNode) {
    if (pNode->ip == ip && pNode->port == port) {
      break;
    }
    pNode = pNode->next;
  }

  if (pNode) {
    return pNode->data;
  }
  return NULL;
}