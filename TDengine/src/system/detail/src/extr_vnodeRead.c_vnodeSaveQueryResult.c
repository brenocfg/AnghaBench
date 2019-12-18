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
typedef  scalar_t__ uint64_t ;
typedef  int int32_t ;
struct TYPE_10__ {int pointsRead; int pointsReturned; scalar_t__ over; int bufIndex; TYPE_1__* pMeterQuerySupporter; int /*<<< orphan*/  signature; } ;
struct TYPE_9__ {TYPE_3__* ahandle; void* thandle; int /*<<< orphan*/ * msg; int /*<<< orphan*/  fp; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pSidSet; } ;
typedef  TYPE_2__ SSchedMsg ;
typedef  TYPE_3__ SQInfo ;

/* Variables and functions */
 scalar_t__ TSDB_QINFO_SET_QUERY_FLAG (TYPE_3__*) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_3__*,...) ; 
 int /*<<< orphan*/  queryQhandle ; 
 int /*<<< orphan*/  taosScheduleTask (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int vnodeCopyQueryResultToMsg (TYPE_3__*,char*,int,int*) ; 
 int /*<<< orphan*/  vnodeMultiMeterQuery ; 
 int /*<<< orphan*/  vnodeQueryData ; 
 int /*<<< orphan*/  vnodeSingleMeterQuery ; 

int vnodeSaveQueryResult(void *handle, char *data, int32_t *size) {
  SQInfo *pQInfo = (SQInfo *)handle;

  // the remained number of retrieved rows, not the interpolated result
  int numOfRows = pQInfo->pointsRead - pQInfo->pointsReturned;

  int32_t numOfFinal = vnodeCopyQueryResultToMsg(pQInfo, data, numOfRows, size);
  pQInfo->pointsReturned += numOfFinal;

  dTrace("QInfo:%p %d are returned, totalReturned:%d totalRead:%d", pQInfo, numOfFinal, pQInfo->pointsReturned,
         pQInfo->pointsRead);

  if (pQInfo->over == 0) {
    //dTrace("QInfo:%p set query flag, oldSig:%p, func:%s", pQInfo, pQInfo->signature, __FUNCTION__);
    dTrace("QInfo:%p set query flag, oldSig:%p", pQInfo, pQInfo->signature);
    uint64_t oldSignature = TSDB_QINFO_SET_QUERY_FLAG(pQInfo);

    /*
     * If SQInfo has been released, the value of signature cannot be equalled to
     * the address of pQInfo, since in release function, the original value has
     * been
     * destroyed. However, this memory area may be reused by another function.
     * It may be 0 or any value, but it is rarely still be equalled to the address
     * of SQInfo.
     */
    if (oldSignature == 0 || oldSignature != (uint64_t)pQInfo) {
      dTrace("%p freed or killed, old sig:%p abort query", pQInfo, oldSignature);
    } else {
      dTrace("%p add query into task queue for schedule", pQInfo);

      SSchedMsg schedMsg;

      if (pQInfo->pMeterQuerySupporter != NULL) {
        if (pQInfo->pMeterQuerySupporter->pSidSet == NULL) {
          schedMsg.fp = vnodeSingleMeterQuery;
        } else {  // group by tag
          schedMsg.fp = vnodeMultiMeterQuery;
        }
      } else {
        pQInfo->bufIndex = pQInfo->bufIndex ^ 1;  // exchange between 0 and 1
        schedMsg.fp = vnodeQueryData;
      }

      schedMsg.msg = NULL;
      schedMsg.thandle = (void *)1;
      schedMsg.ahandle = pQInfo;
      taosScheduleTask(queryQhandle, &schedMsg);
    }
  }

  return numOfFinal;
}