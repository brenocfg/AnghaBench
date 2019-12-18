#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  long int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_9__ {long slidingTime; scalar_t__ stime; scalar_t__ etime; scalar_t__ interval; scalar_t__ precision; int /*<<< orphan*/  param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pSql; } ;
typedef  TYPE_1__ SSqlStream ;
typedef  TYPE_2__ SSqlObj ;

/* Variables and functions */
 scalar_t__ TSDB_TIME_PRECISION_MICRO ; 
 scalar_t__ isProjectStream (int /*<<< orphan*/ *) ; 
 long rand () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 long taosGetTimestamp (scalar_t__) ; 
 int /*<<< orphan*/  taos_close_stream (TYPE_1__*) ; 
 long tsMaxStreamComputDelay ; 
 int /*<<< orphan*/  tscSetRetryTimer (TYPE_1__*,TYPE_2__*,long) ; 
 int /*<<< orphan*/  tscTrace (char*,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void tscSetNextLaunchTimer(SSqlStream *pStream, SSqlObj *pSql) {
  int64_t timer = 0;

  if (isProjectStream(&pSql->cmd)) {
    /*
     * for project query, no mater fetch data successfully or not, next launch will issue
     * more than the sliding time window
     */
    timer = pStream->slidingTime;
    if (pStream->stime > pStream->etime) {
      tscTrace("%p stream:%p, stime:%lld is larger than end time: %lld, stop the stream", pStream->pSql, pStream,
               pStream->stime, pStream->etime);
      // TODO : How to terminate stream here
      taos_close_stream(pStream);
      if (pStream->callback) {
        // Callback function from upper level
        pStream->callback(pStream->param);
      }
      return;
    }
  } else {
    pStream->stime += pStream->slidingTime;
    if ((pStream->stime - pStream->interval) >= pStream->etime) {
      tscTrace("%p stream:%p, stime:%ld is larger than end time: %ld, stop the stream", pStream->pSql, pStream,
               pStream->stime, pStream->etime);
      // TODO : How to terminate stream here
      taos_close_stream(pStream);
      if (pStream->callback) {
        // Callback function from upper level
        pStream->callback(pStream->param);
      }
      return;
    }

    timer = pStream->stime - taosGetTimestamp(pStream->precision);
    if (timer < 0) {
      timer = 0;
    }
  }

  int64_t delayDelta = (int64_t)(pStream->slidingTime * 0.1);
  delayDelta = (rand() % delayDelta);

  int64_t maxDelay =
      (pStream->precision == TSDB_TIME_PRECISION_MICRO) ? tsMaxStreamComputDelay * 1000L : tsMaxStreamComputDelay;

  if (delayDelta > maxDelay) {
    delayDelta = maxDelay;
  }

  timer += delayDelta;  // a random number
  if (pStream->precision == TSDB_TIME_PRECISION_MICRO) {
    timer = timer / 1000L;
  }

  tscSetRetryTimer(pStream, pSql, timer);
}