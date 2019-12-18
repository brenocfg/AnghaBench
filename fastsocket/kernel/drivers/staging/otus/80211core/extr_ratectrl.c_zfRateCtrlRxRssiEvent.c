#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u16_t ;
struct zsRcCell {scalar_t__ rxRssi; int probingTime; } ;

/* Variables and functions */
 int ZM_MS_PER_TICK ; 
 int ZM_RATE_CTRL_PROBING_INTERVAL_MS ; 
 scalar_t__ ZM_RATE_CTRL_RSSI_VARIATION ; 

void zfRateCtrlRxRssiEvent(struct zsRcCell* rcCell, u16_t rxRssi)
{
    /* if delta(rcCell->rxRssi, rxRssi) > ZM_RATE_CTRL_RSSI_VARIATION */
    if ((rcCell->rxRssi - rxRssi) > ZM_RATE_CTRL_RSSI_VARIATION)
    {
        /* Accelerate rate probing via decreaing rcCell->probingTime */
        rcCell->probingTime -= ZM_RATE_CTRL_PROBING_INTERVAL_MS/ZM_MS_PER_TICK;
    }

    /* Update RSSI moving average */
    rcCell->rxRssi = (((rcCell->rxRssi*7) + rxRssi)+4) >> 3;
    return;
}