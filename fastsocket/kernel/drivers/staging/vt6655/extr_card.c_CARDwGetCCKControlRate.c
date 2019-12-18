#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int UINT ;
struct TYPE_2__ {int wBasicRate; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 int RATE_1M ; 

WORD CARDwGetCCKControlRate(PVOID pDeviceHandler, WORD wRateIdx)
{
    PSDevice    pDevice = (PSDevice) pDeviceHandler;
    UINT ui = (UINT)wRateIdx;

    while (ui > RATE_1M) {
        if (pDevice->wBasicRate & ((WORD)1 << ui)) {
            return (WORD)ui;
        }
        ui --;
    }
    return (WORD)RATE_1M;
}