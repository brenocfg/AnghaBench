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

/* Variables and functions */
 int /*<<< orphan*/  BTM_DEV_STATUS_DOWN ; 
 int /*<<< orphan*/  BTM_DeviceReset (int /*<<< orphan*/ *) ; 
 scalar_t__ BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  HCI_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_report_device_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_hardware_error_evt (UINT8 *p)
{
    HCI_TRACE_ERROR("Ctlr H/w error event - code:0x%x\n", *p);

    /* If anyone wants device status notifications, give him one. */
    btm_report_device_status (BTM_DEV_STATUS_DOWN);

    /* Reset the controller */
    if (BTM_IsDeviceUp()) {
        BTM_DeviceReset (NULL);
    }
}