#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ stime; scalar_t__ etime; } ;
struct TYPE_9__ {int /*<<< orphan*/ * msg; void* thandle; TYPE_1__* ahandle; int /*<<< orphan*/  fp; } ;
struct TYPE_8__ {TYPE_6__ cmd; } ;
struct TYPE_7__ {void* pTimer; scalar_t__ stime; scalar_t__ etime; scalar_t__ interval; int /*<<< orphan*/  precision; TYPE_2__* pSql; scalar_t__ numOfRes; } ;
typedef  TYPE_1__ SSqlStream ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSchedMsg ;

/* Variables and functions */
 scalar_t__ isProjectStream (TYPE_6__*) ; 
 scalar_t__ taosGetTimestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  tscProcessStreamLaunchQuery ; 
 int /*<<< orphan*/  tscQhandle ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*) ; 

__attribute__((used)) static void tscProcessStreamTimer(void *handle, void *tmrId) {
  SSqlStream *pStream = (SSqlStream *)handle;
  if (pStream == NULL) return;
  if (pStream->pTimer != tmrId) return;
  pStream->pTimer = NULL;

  pStream->numOfRes = 0;  // reset the numOfRes.
  SSqlObj *pSql = pStream->pSql;
  tscTrace("%p add into timer", pSql);

  if (isProjectStream(&pSql->cmd)) {
    /*
     * pSql->cmd.etime, which is the start time, does not change in case of
     * repeat first execution, once the first execution failed.
     */
    pSql->cmd.stime = pStream->stime;  // start time

    pSql->cmd.etime = taosGetTimestamp(pStream->precision);  // end time
    if (pSql->cmd.etime > pStream->etime) {
      pSql->cmd.etime = pStream->etime;
    }
  } else {
    pSql->cmd.stime = pStream->stime - pStream->interval;
    pSql->cmd.etime = pStream->stime - 1;
  }

  // launch stream computing in a new thread
  SSchedMsg schedMsg;
  schedMsg.fp = tscProcessStreamLaunchQuery;
  schedMsg.ahandle = pStream;
  schedMsg.thandle = (void *)1;
  schedMsg.msg = NULL;
  taosScheduleTask(tscQhandle, &schedMsg);
}