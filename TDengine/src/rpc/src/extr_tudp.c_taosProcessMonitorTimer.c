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
struct TYPE_6__ {void* pTimer; int /*<<< orphan*/  ip; scalar_t__ dataLen; int /*<<< orphan*/  data; TYPE_1__* pSet; } ;
struct TYPE_5__ {int /*<<< orphan*/  tmrCtrl; int /*<<< orphan*/  shandle; int /*<<< orphan*/  (* fp ) (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ SUdpConnSet ;
typedef  TYPE_2__ SMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (void (*) (void*,void*),int,TYPE_2__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  taosTmrStopA (void**) ; 

void taosProcessMonitorTimer(void *param, void *tmrId) {
  SMonitor *pMonitor = (SMonitor *)param;
  if (pMonitor->pTimer != tmrId) return;

  SUdpConnSet *pSet = pMonitor->pSet;
  pMonitor->pTimer = NULL;

  if (pSet) {
    char *data = malloc((size_t)pMonitor->dataLen);
    memcpy(data, pMonitor->data, (size_t)pMonitor->dataLen);

    tTrace("%s monitor timer is expired, update the link status", pSet->label);
    (*pSet->fp)(data, pMonitor->dataLen, pMonitor->ip, 0, pSet->shandle, NULL, NULL);
    taosTmrReset(taosProcessMonitorTimer, 200, pMonitor, pSet->tmrCtrl, &pMonitor->pTimer);
  } else {
    taosTmrStopA(&pMonitor->pTimer);
    free(pMonitor);
  }
}