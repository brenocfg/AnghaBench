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
struct TYPE_9__ {TYPE_1__* prev; struct TYPE_9__* next; int /*<<< orphan*/  string; } ;
struct TYPE_8__ {scalar_t__ maxSessions; TYPE_3__** hashList; } ;
struct TYPE_7__ {TYPE_3__* next; } ;
typedef  TYPE_2__ SHashObj ;
typedef  TYPE_3__ SHashNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int sdbHashString (TYPE_2__*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void sdbDeleteStrHash(void *handle, void *key) {
  int        hash;
  SHashNode *pNode;
  SHashObj * pObj;
  char *     string = (char *)key;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return;

  hash = sdbHashString(pObj, string);
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

    memset(pNode, 0, sizeof(SHashNode));
    free(pNode);
  }
}