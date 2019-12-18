#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_5__ {int queueSize; char* label; int /*<<< orphan*/  numOfThreads; int /*<<< orphan*/ * qthread; scalar_t__ emptySlot; scalar_t__ fullSlot; struct TYPE_5__* queue; int /*<<< orphan*/  fullSem; int /*<<< orphan*/  emptySem; int /*<<< orphan*/  queueMutex; } ;
typedef  TYPE_1__ SSchedQueue ;
typedef  TYPE_1__ SSchedMsg ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pError (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pTrace (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  taosCleanUpScheduler (TYPE_1__*) ; 
 int /*<<< orphan*/  taosProcessSchedQueue ; 
 scalar_t__ tsem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

void *taosInitScheduler(int queueSize, int numOfThreads, const char *label) {
  pthread_attr_t attr;
  SSchedQueue *  pSched = (SSchedQueue *)malloc(sizeof(SSchedQueue));
  if (pSched == NULL) {
    pError("%s: no enough memory for pSched, reason: %s", label, strerror(errno));
    goto _error;
  }

  memset(pSched, 0, sizeof(SSchedQueue));
  pSched->queueSize = queueSize;
  strncpy(pSched->label, label, sizeof(pSched->label)); // fix buffer overflow
  pSched->label[sizeof(pSched->label)-1] = '\0';

  if (pthread_mutex_init(&pSched->queueMutex, NULL) < 0) {
    pError("init %s:queueMutex failed, reason:%s", pSched->label, strerror(errno));
    goto _error;
  }

  if (tsem_init(&pSched->emptySem, 0, (unsigned int)pSched->queueSize) != 0) {
    pError("init %s:empty semaphore failed, reason:%s", pSched->label, strerror(errno));
    goto _error;
  }

  if (tsem_init(&pSched->fullSem, 0, 0) != 0) {
    pError("init %s:full semaphore failed, reason:%s", pSched->label, strerror(errno));
    goto _error;
  }

  if ((pSched->queue = (SSchedMsg *)malloc((size_t)pSched->queueSize * sizeof(SSchedMsg))) == NULL) {
    pError("%s: no enough memory for queue, reason:%s", pSched->label, strerror(errno));
    goto _error;
  }

  memset(pSched->queue, 0, (size_t)pSched->queueSize * sizeof(SSchedMsg));
  pSched->fullSlot = 0;
  pSched->emptySlot = 0;

  pSched->qthread = malloc(sizeof(pthread_t) * (size_t)numOfThreads);
  if (pSched->qthread == NULL) {
    pError("%s: no enough memory for qthread, reason: %s", pSched->label, strerror(errno));
    goto _error;
  }

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < numOfThreads; ++i) {
    if (pthread_create(pSched->qthread + i, &attr, taosProcessSchedQueue, (void *)pSched) != 0) {
      pError("%s: failed to create rpc thread, reason:%s", pSched->label, strerror(errno));
      goto _error;
    }
    ++pSched->numOfThreads;
  }

  pTrace("%s scheduler is initialized, numOfThreads:%d", pSched->label, pSched->numOfThreads);

  return (void *)pSched;

_error:
  taosCleanUpScheduler(pSched);
  return NULL;
}