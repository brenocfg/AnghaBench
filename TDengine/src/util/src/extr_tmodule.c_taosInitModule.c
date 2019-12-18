#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_4__ {char* name; int (* init ) () ;int /*<<< orphan*/  thread; scalar_t__ emptySlot; scalar_t__ fullSlot; scalar_t__ queueSize; int /*<<< orphan*/ * queue; int /*<<< orphan*/  fullSem; int /*<<< orphan*/  emptySem; int /*<<< orphan*/  stmMutex; int /*<<< orphan*/  queueMutex; } ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int stub1 () ; 
 int /*<<< orphan*/  taosCleanUpModule (TYPE_1__*) ; 
 int /*<<< orphan*/  taosProcessQueue ; 
 scalar_t__ tsem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

int taosInitModule(module_t *pMod) {
  pthread_attr_t attr;

  if (pthread_mutex_init(&pMod->queueMutex, NULL) < 0) {
    printf("ERROR: init %s queueMutex failed, reason:%s\n", pMod->name, strerror(errno));
    taosCleanUpModule(pMod);
    return -1;
  }

  if (pthread_mutex_init(&pMod->stmMutex, NULL) < 0) {
    printf("ERROR: init %s stmMutex failed, reason:%s\n", pMod->name, strerror(errno));
    taosCleanUpModule(pMod);
    return -1;
  }

  if (tsem_init(&pMod->emptySem, 0, (unsigned int)pMod->queueSize) != 0) {
    printf("ERROR: init %s empty semaphore failed, reason:%s\n", pMod->name, strerror(errno));
    taosCleanUpModule(pMod);
    return -1;
  }

  if (tsem_init(&pMod->fullSem, 0, 0) != 0) {
    printf("ERROR: init %s full semaphore failed, reason:%s\n", pMod->name, strerror(errno));
    taosCleanUpModule(pMod);
    return -1;
  }

  if ((pMod->queue = (msg_t *)malloc((size_t)pMod->queueSize * sizeof(msg_t))) == NULL) {
    printf("ERROR: %s no enough memory, reason:%s\n", pMod->name, strerror(errno));
    taosCleanUpModule(pMod);
    return -1;
  }

  memset(pMod->queue, 0, (size_t)pMod->queueSize * sizeof(msg_t));
  pMod->fullSlot = 0;
  pMod->emptySlot = 0;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  if (pthread_create(&pMod->thread, &attr, taosProcessQueue, (void *)pMod) != 0) {
    printf("ERROR: %s failed to create thread, reason:%s\n", pMod->name, strerror(errno));
    taosCleanUpModule(pMod);
    return -1;
  }

  if (pMod->init) return (*(pMod->init))();

  return 0;
}