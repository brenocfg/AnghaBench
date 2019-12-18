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
struct TYPE_5__ {void* data; void* string; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
struct TYPE_4__ {scalar_t__ maxSessions; size_t (* hashFp ) (TYPE_1__*,char*) ;int /*<<< orphan*/  mutex; TYPE_2__** hashList; } ;
typedef  TYPE_1__ SHashObj ;
typedef  TYPE_2__ SHashNode ;

/* Variables and functions */
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 int /*<<< orphan*/  pTrace (char*,size_t,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 
 scalar_t__ strlen (char*) ; 
 size_t stub1 (TYPE_1__*,char*) ; 

void *taosAddStrHashWithSize(void *handle, char *string, char *pData, int dataSize) {
  uint32_t   hash;
  SHashNode *pNode;
  SHashObj * pObj;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return NULL;
  if (string == NULL || string[0] == 0) return NULL;

  hash = (*pObj->hashFp)(pObj, string);

  pthread_mutex_lock(&pObj->mutex);

  pNode = (SHashNode *)malloc(sizeof(SHashNode) + (size_t)dataSize + strlen(string) + 1);
  memcpy(pNode->data, pData, (size_t)dataSize);
  pNode->prev = 0;
  pNode->next = pObj->hashList[hash];
  pNode->string = pNode->data + dataSize;
  strcpy(pNode->string, string);

  if (pObj->hashList[hash] != 0) (pObj->hashList[hash])->prev = pNode;
  pObj->hashList[hash] = pNode;

  pthread_mutex_unlock(&pObj->mutex);

  pTrace("hash:%d:%s is added", hash, string);

  return pNode->data;
}