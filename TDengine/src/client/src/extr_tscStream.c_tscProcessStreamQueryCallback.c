#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {TYPE_3__* pSql; int /*<<< orphan*/  precision; int /*<<< orphan*/  slidingTime; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ SSqlStream ;
typedef  int /*<<< orphan*/  SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  taos_fetch_rows_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tscClearMeterMetaInfo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tscGetMeterMetaInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscGetRetryDelayTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscProcessStreamRetrieveResult ; 
 int /*<<< orphan*/  tscSetRetryTimer (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tscProcessStreamQueryCallback(void *param, TAOS_RES *tres, int numOfRows) {
  SSqlStream *pStream = (SSqlStream *)param;
  if (tres == NULL || numOfRows < 0) {
    int64_t retryDelay = tscGetRetryDelayTime(pStream->slidingTime, pStream->precision);
    tscError("%p stream:%p, query data failed, code:%d, retry in %lldms", pStream->pSql, pStream, numOfRows,
             retryDelay);

    SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(&pStream->pSql->cmd, 0);
    tscClearMeterMetaInfo(pMeterMetaInfo, true);

    tscSetRetryTimer(pStream, pStream->pSql, retryDelay);
    return;
  }

  taos_fetch_rows_a(tres, tscProcessStreamRetrieveResult, param);
}