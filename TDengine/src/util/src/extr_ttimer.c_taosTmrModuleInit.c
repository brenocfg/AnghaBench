#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmr_obj_t ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_1__ tmr_ctrl_t ;
typedef  int /*<<< orphan*/  timer_list_t ;
struct TYPE_10__ {scalar_t__ size; int /*<<< orphan*/ ** slots; scalar_t__ index; scalar_t__ resolution; scalar_t__ nextScanAt; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ time_wheel_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {int /*<<< orphan*/ * slots; scalar_t__ size; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSECONDS_PER_TICK ; 
 scalar_t__ calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int tListLen (TYPE_2__*) ; 
 scalar_t__ taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosInitScheduler (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taosInitTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int taosMaxTmrCtrl ; 
 int /*<<< orphan*/  taosTimerLoopFunc ; 
 int /*<<< orphan*/  taosTmrThreads ; 
 TYPE_6__ timerMap ; 
 int /*<<< orphan*/  tmrCtrlMutex ; 
 TYPE_1__* tmrCtrls ; 
 int /*<<< orphan*/  tmrError (char*,...) ; 
 int /*<<< orphan*/  tmrQhandle ; 
 int /*<<< orphan*/  tmrTrace (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* unusedTmrCtrl ; 
 TYPE_2__* wheels ; 

__attribute__((used)) static void taosTmrModuleInit(void) {
  tmrCtrls = malloc(sizeof(tmr_ctrl_t) * taosMaxTmrCtrl);
  if (tmrCtrls == NULL) {
    tmrError("failed to allocate memory for timer controllers.");
    return;
  }

  for (int i = 0; i < taosMaxTmrCtrl - 1; ++i) {
    tmr_ctrl_t* ctrl = tmrCtrls + i;
    ctrl->next = ctrl + 1;
  }
  unusedTmrCtrl = tmrCtrls;

  pthread_mutex_init(&tmrCtrlMutex, NULL);

  int64_t now = taosGetTimestampMs();
  for (int i = 0; i < tListLen(wheels); i++) {
    time_wheel_t* wheel = wheels + i;
    if (pthread_mutex_init(&wheel->mutex, NULL) != 0) {
      tmrError("failed to create the mutex for wheel, reason:%s", strerror(errno));
      return;
    }
    wheel->nextScanAt = now + wheel->resolution;
    wheel->index = 0;
    wheel->slots = (tmr_obj_t**)calloc(wheel->size, sizeof(tmr_obj_t*));
    if (wheel->slots == NULL) {
      tmrError("failed to allocate wheel slots");
      return;
    }
    timerMap.size += wheel->size;
  }

  timerMap.count = 0;
  timerMap.slots = (timer_list_t*)calloc(timerMap.size, sizeof(timer_list_t));
  if (timerMap.slots == NULL) {
    tmrError("failed to allocate hash map");
    return;
  }

  tmrQhandle = taosInitScheduler(10000, taosTmrThreads, "tmr");
  taosInitTimer(taosTimerLoopFunc, MSECONDS_PER_TICK);

  tmrTrace("timer module is initialized, number of threads: %d", taosTmrThreads);
}