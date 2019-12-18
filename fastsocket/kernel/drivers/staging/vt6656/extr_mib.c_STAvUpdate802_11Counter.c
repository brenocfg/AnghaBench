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
typedef  void* ULONGLONG ;
struct TYPE_6__ {void* MulticastReceivedFrameCount; int /*<<< orphan*/  FCSErrorCount; int /*<<< orphan*/  ACKFailureCount; int /*<<< orphan*/  RTSFailureCount; int /*<<< orphan*/  RTSSuccessCount; void* MultipleRetryCount; void* RetryCount; void* FailedCount; void* MulticastTransmittedFrameCount; } ;
struct TYPE_5__ {scalar_t__ dwRsrMulticast; scalar_t__ dwRsrBroadcast; scalar_t__ dwTsrMoreThanOnceRetry; scalar_t__ dwTsrRetry; scalar_t__ dwTsrErr; scalar_t__ dwTsrMulticast; scalar_t__ dwTsrBroadcast; } ;
typedef  TYPE_1__* PSStatCounter ;
typedef  TYPE_2__* PSDot11Counters ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */

void
STAvUpdate802_11Counter(
    PSDot11Counters         p802_11Counter,
    PSStatCounter           pStatistic,
    BYTE                    byRTSSuccess,
    BYTE                    byRTSFail,
    BYTE                    byACKFail,
    BYTE                    byFCSErr
    )
{
    //p802_11Counter->TransmittedFragmentCount
    p802_11Counter->MulticastTransmittedFrameCount = (ULONGLONG) (pStatistic->dwTsrBroadcast +
                                                                  pStatistic->dwTsrMulticast);
    p802_11Counter->FailedCount = (ULONGLONG) (pStatistic->dwTsrErr);
    p802_11Counter->RetryCount = (ULONGLONG) (pStatistic->dwTsrRetry);
    p802_11Counter->MultipleRetryCount = (ULONGLONG) (pStatistic->dwTsrMoreThanOnceRetry);
    //p802_11Counter->FrameDuplicateCount
    p802_11Counter->RTSSuccessCount += (ULONGLONG) byRTSSuccess;
    p802_11Counter->RTSFailureCount += (ULONGLONG) byRTSFail;
    p802_11Counter->ACKFailureCount += (ULONGLONG) byACKFail;
    p802_11Counter->FCSErrorCount +=   (ULONGLONG) byFCSErr;
    //p802_11Counter->ReceivedFragmentCount
    p802_11Counter->MulticastReceivedFrameCount = (ULONGLONG) (pStatistic->dwRsrBroadcast +
                                                               pStatistic->dwRsrMulticast);
}