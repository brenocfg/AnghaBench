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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_acl_packet_size_ble ) () ;} ;

/* Variables and functions */
 TYPE_1__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

UINT16 BTU_BleAclPktSize(void)
{
#if BLE_INCLUDED == TRUE
    return controller_get_interface()->get_acl_packet_size_ble();
#else
    return 0;
#endif
}