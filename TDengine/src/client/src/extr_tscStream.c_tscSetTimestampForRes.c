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
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_10__ {TYPE_2__ res; } ;
struct TYPE_8__ {scalar_t__ stime; scalar_t__ interval; } ;
typedef  TYPE_1__ SSqlStream ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  tscWarn (char*,TYPE_3__*,TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void tscSetTimestampForRes(SSqlStream *pStream, SSqlObj *pSql) {
  SSqlRes *pRes = &pSql->res;

  int64_t  timestamp = *(int64_t *)pRes->data;
  int64_t actualTimestamp = pStream->stime - pStream->interval;

  if (timestamp != actualTimestamp) {
    // reset the timestamp of each agg point by using start time of each interval
    *((int64_t *)pRes->data) = actualTimestamp;
    tscWarn("%p stream:%p, timestamp of points is:%lld, reset to %lld", pSql, pStream, timestamp, actualTimestamp);
  }
}