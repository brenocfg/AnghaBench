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
struct TYPE_5__ {char* name; size_t emptySlot; int queueSize; int /*<<< orphan*/  fullSem; int /*<<< orphan*/  queueMutex; TYPE_1__* queue; int /*<<< orphan*/  emptySem; } ;
typedef  TYPE_2__ module_t ;
struct TYPE_4__ {int cid; int mid; int tid; char* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ tsem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ tsem_wait (int /*<<< orphan*/ *) ; 

int taosSendMsgToModule(module_t *pMod, int cid, int mid, int tid, char *msg) {
  if (tsem_wait(&pMod->emptySem) != 0)
    printf("ERROR: wait %s emptySem failed, reason:%s\n", pMod->name, strerror(errno));

  if (pthread_mutex_lock(&pMod->queueMutex) != 0)
    printf("ERROR: lock %s queueMutex failed, reason:%s\n", pMod->name, strerror(errno));

  pMod->queue[pMod->emptySlot].cid = cid;
  pMod->queue[pMod->emptySlot].mid = mid;
  pMod->queue[pMod->emptySlot].tid = tid;
  pMod->queue[pMod->emptySlot].msg = msg;
  pMod->emptySlot = (pMod->emptySlot + 1) % pMod->queueSize;

  if (pthread_mutex_unlock(&pMod->queueMutex) != 0)
    printf("ERROR: unlock %s queueMutex failed, reason:%s\n", pMod->name, strerror(errno));

  if (tsem_post(&pMod->fullSem) != 0) printf("ERROR: post %s fullSem failed, reason:%s\n", pMod->name, strerror(errno));

  return 0;
}