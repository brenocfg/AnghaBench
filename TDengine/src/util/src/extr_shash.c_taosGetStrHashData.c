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
typedef  size_t uint32_t ;
struct TYPE_5__ {void* data; struct TYPE_5__* next; int /*<<< orphan*/  string; } ;
struct TYPE_4__ {scalar_t__ maxSessions; size_t (* hashFp ) (TYPE_1__*,char*) ;int /*<<< orphan*/  mutex; TYPE_2__** hashList; } ;
typedef  TYPE_1__ SHashObj ;
typedef  TYPE_2__ SHashNode ;

/* Variables and functions */
 int /*<<< orphan*/  pTrace (char*,size_t,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t stub1 (TYPE_1__*,char*) ; 

void *taosGetStrHashData(void *handle, char *string) {
  uint32_t   hash;
  SHashNode *pNode;
  SHashObj * pObj;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return NULL;
  if (string == NULL || string[0] == 0) return NULL;

  hash = (*pObj->hashFp)(pObj, string);

  pthread_mutex_lock(&pObj->mutex);

  pNode = pObj->hashList[hash];

  while (pNode) {
    if (strcmp(pNode->string, string) == 0) {
      pTrace("hash:%d:%s is retrieved", hash, string);
      break;
    }

    pNode = pNode->next;
  }

  pthread_mutex_unlock(&pObj->mutex);

  if (pNode) return pNode->data;

  return NULL;
}