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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_pm_proc_mode_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sco_chk_pend_unpark (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_mode_change_evt (UINT8 *p)
{
    UINT8       status;
    UINT16      handle;
    UINT8       current_mode;
    UINT16      interval;

    STREAM_TO_UINT8 (status, p);

    STREAM_TO_UINT16 (handle, p);
    STREAM_TO_UINT8 (current_mode, p);
    STREAM_TO_UINT16 (interval, p);
#if BTM_SCO_WAKE_PARKED_LINK == TRUE
    btm_sco_chk_pend_unpark (status, handle);
#endif
    btm_pm_proc_mode_change (status, handle, current_mode, interval);

    /*
    #if (HID_DEV_INCLUDED == TRUE) && (HID_DEV_PM_INCLUDED == TRUE)
        hidd_pm_proc_mode_change( status, current_mode, interval ) ;
    #endif
    */
}