#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  abyCntTxPattern; scalar_t__ dwCntTxBufLength; } ;
typedef  TYPE_1__* PSStatCounter ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
STAvUpdateTDStatCounterEx (
    PSStatCounter   pStatistic,
    PBYTE           pbyBuffer,
    DWORD           cbFrameLength
    )
{
    UINT    uPktLength;

    uPktLength = (UINT)cbFrameLength;

    // tx length
    pStatistic->dwCntTxBufLength = uPktLength;
    // tx pattern, we just see 16 bytes for sample
    memcpy(pStatistic->abyCntTxPattern, pbyBuffer, 16);
}