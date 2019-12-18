#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {scalar_t__ nAggTimeInterval; scalar_t__ nSlidingTime; } ;
struct TYPE_9__ {TYPE_3__ cmd; } ;
struct TYPE_8__ {scalar_t__ precision; scalar_t__ interval; scalar_t__ slidingTime; } ;
typedef  TYPE_1__ SSqlStream ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_TIME_PRECISION_MICRO ; 
 long tsMinIntervalTime ; 
 long tsMinSlidingTime ; 
 int /*<<< orphan*/  tscWarn (char*,TYPE_2__*,TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void tscSetSlidingWindowInfo(SSqlObj *pSql, SSqlStream *pStream) {
  SSqlCmd *pCmd = &pSql->cmd;

  int64_t minIntervalTime =
      (pStream->precision == TSDB_TIME_PRECISION_MICRO) ? tsMinIntervalTime * 1000L : tsMinIntervalTime;
  if (pCmd->nAggTimeInterval < minIntervalTime) {
    tscWarn("%p stream:%p, original sample interval:%ld too small, reset to:%lld", pSql, pStream,
            pCmd->nAggTimeInterval, minIntervalTime);
    pCmd->nAggTimeInterval = minIntervalTime;
  }

  pStream->interval = pCmd->nAggTimeInterval;  // it shall be derived from sql string

  if (pCmd->nSlidingTime == 0) {
    pCmd->nSlidingTime = pCmd->nAggTimeInterval;
  }

  int64_t minSlidingTime =
      (pStream->precision == TSDB_TIME_PRECISION_MICRO) ? tsMinSlidingTime * 1000L : tsMinSlidingTime;

  if (pCmd->nSlidingTime < minSlidingTime) {
    tscWarn("%p stream:%p, original sliding value:%lld too small, reset to:%lld", pSql, pStream, pCmd->nSlidingTime,
            minSlidingTime);

    pCmd->nSlidingTime = minSlidingTime;
  }

  if (pCmd->nSlidingTime > pCmd->nAggTimeInterval) {
    tscWarn("%p stream:%p, sliding value:%lld can not be larger than interval range, reset to:%lld", pSql, pStream,
            pCmd->nSlidingTime, pCmd->nAggTimeInterval);

    pCmd->nSlidingTime = pCmd->nAggTimeInterval;
  }

  pStream->slidingTime = pCmd->nSlidingTime;
}