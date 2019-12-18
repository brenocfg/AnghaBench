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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ maxSessions; TYPE_1__** longHashList; } ;
struct TYPE_4__ {scalar_t__ key; void* data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SLongHash ;
typedef  TYPE_2__ SHashObj ;

/* Variables and functions */
 int sdbHashLong (TYPE_2__*,scalar_t__) ; 

void *sdbGetIntHashData(void *handle, void *pKey) {
  int        hash;
  SLongHash *pNode;
  SHashObj * pObj;
  uint32_t   key = *((uint32_t *)pKey);

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return NULL;

  hash = sdbHashLong(pObj, key);
  pNode = pObj->longHashList[hash];

  while (pNode) {
    if (pNode->key == key) {
      break;
    }
    pNode = pNode->next;
  }

  if (pNode) return pNode->data;

  return NULL;
}