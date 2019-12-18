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
struct TYPE_5__ {void* data; struct TYPE_5__* next; int /*<<< orphan*/  string; } ;
struct TYPE_4__ {scalar_t__ maxSessions; TYPE_2__** hashList; } ;
typedef  TYPE_1__ SHashObj ;
typedef  TYPE_2__ SHashNode ;

/* Variables and functions */
 int sdbHashString (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void *sdbGetStrHashData(void *handle, void *key) {
  int        hash;
  SHashNode *pNode;
  SHashObj * pObj;
  char *     string = (char *)key;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return NULL;

  hash = sdbHashString(pObj, string);
  pNode = pObj->hashList[hash];

  while (pNode) {
    if (strcmp(pNode->string, string) == 0) {
      break;
    }
    pNode = pNode->next;
  }

  if (pNode) return pNode->data;

  return NULL;
}