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
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int ATH_CWM_EXTCH_BUSY_THRESHOLD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

u16_t zfCwmIsExtChanBusy(u32_t ctlBusy, u32_t extBusy)
{
    u32_t busy; /* percentage */
    u32_t cycleTime, ctlClear;

    cycleTime = 1280000; //1.28 seconds

    if (cycleTime > ctlBusy) {
        ctlClear = cycleTime - ctlBusy;
    }
    else
    {
        ctlClear = 0;
    }

    /* Compute ratio of extension channel busy to control channel clear
     * as an approximation to extension channel cleanliness.
     *
     * According to the hardware folks, ext rxclear is undefined
     * if the ctrl rxclear is de-asserted (i.e. busy)
     */
    if (ctlClear) {
        busy = (extBusy * 100) / ctlClear;
    } else {
        busy = 0;
    }
    if (busy > ATH_CWM_EXTCH_BUSY_THRESHOLD) {
        return TRUE;
    }

    return FALSE;
}