#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cid; int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__ msg_t ;
struct TYPE_6__ {char* name; size_t fullSlot; int queueSize; int /*<<< orphan*/  (* processMsg ) (TYPE_1__*) ;int /*<<< orphan*/  emptySem; int /*<<< orphan*/  queueMutex; TYPE_1__* queue; int /*<<< orphan*/  fullSem; } ;
typedef  TYPE_2__ module_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CANCEL_ASYNCHRONOUS ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ maxCid ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcanceltype (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 
 scalar_t__ tsem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ tsem_wait (int /*<<< orphan*/ *) ; 

void *taosProcessQueue(void *param) {
  msg_t     msg;
  module_t *pMod = (module_t *)param;
  int       oldType;

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldType);

  signal(SIGINT, SIG_IGN);

  while (1) {
    if (tsem_wait(&pMod->fullSem) != 0)
      printf("ERROR: wait %s fullSem failed, reason:%s\n", pMod->name, strerror(errno));

    if (pthread_mutex_lock(&pMod->queueMutex) != 0)
      printf("ERROR: lock %s queueMutex failed, reason:%s\n", pMod->name, strerror(errno));

    msg = pMod->queue[pMod->fullSlot];
    memset(&(pMod->queue[pMod->fullSlot]), 0, sizeof(msg_t));
    pMod->fullSlot = (pMod->fullSlot + 1) % pMod->queueSize;

    if (pthread_mutex_unlock(&pMod->queueMutex) != 0)
      printf("ERROR: unlock %s queueMutex failed, reason:%s\n", pMod->name, strerror(errno));

    if (tsem_post(&pMod->emptySem) != 0)
      printf("ERROR: post %s emptySem failed, reason:%s\n", pMod->name, strerror(errno));

    /* process the message */
    if (msg.cid < 0 || msg.cid >= maxCid) {
      /*printf("ERROR: cid:%d is out of range, msg is discarded\n", msg.cid);*/
      continue;
    }

    /*
        if ( pthread_mutex_lock ( &(pMod->stmMutex)) != 0 )
          printf("ERROR: lock %s stmMutex failed, reason:%s\n", pMod->name,
       strerror(errno));
    */
    (*(pMod->processMsg))(&msg);

    tfree(msg.msg);
    /*
        if ( pthread_mutex_unlock ( &(pMod->stmMutex)) != 0 )
          printf("ERROR: unlock %s stmMutex failed, reason:%s\n", pMod->name,
       strerror(errno));
    */
  }
}