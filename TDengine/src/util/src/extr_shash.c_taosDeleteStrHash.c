#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_9__ {TYPE_1__* prev; struct TYPE_9__* next; int /*<<< orphan*/  string; } ;
struct TYPE_8__ {scalar_t__ maxSessions; size_t (* hashFp ) (TYPE_2__*,char*) ;int /*<<< orphan*/  mutex; TYPE_3__** hashList; } ;
struct TYPE_7__ {TYPE_3__* next; } ;
typedef  TYPE_2__ SHashObj ;
typedef  TYPE_3__ SHashNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  pTrace (char*,size_t,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t stub1 (TYPE_2__*,char*) ; 

void taosDeleteStrHash(void *handle, char *string) {
  uint32_t   hash;
  SHashNode *pNode;
  SHashObj * pObj;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return;
  if (string == NULL || string[0] == 0) return;

  hash = (*(pObj->hashFp))(pObj, string);

  pthread_mutex_lock(&pObj->mutex);

  pNode = pObj->hashList[hash];
  while (pNode) {
    if (strcmp(pNode->string, string) == 0) break;

    pNode = pNode->next;
  }

  if (pNode) {
    if (pNode->prev) {
      pNode->prev->next = pNode->next;
    } else {
      pObj->hashList[hash] = pNode->next;
    }

    if (pNode->next) {
      pNode->next->prev = pNode->prev;
    }

    pTrace("hash:%d:%s:%p is removed", hash, string, pNode);

    free(pNode);
  }

  pthread_mutex_unlock(&pObj->mutex);
}