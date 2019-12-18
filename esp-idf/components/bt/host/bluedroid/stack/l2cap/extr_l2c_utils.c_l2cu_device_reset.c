#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ handle; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_4__ {int /*<<< orphan*/  is_ble_connecting; TYPE_1__* lcb_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HCI_INVALID_HANDLE ; 
 int MAX_L2CAP_LINKS ; 
 int /*<<< orphan*/  l2c_link_hci_disc_comp (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ l2cb ; 

void l2cu_device_reset (void)
{
    int         xx;
    tL2C_LCB    *p_lcb = &l2cb.lcb_pool[0];

    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p_lcb++) {
        if ((p_lcb->in_use) && (p_lcb->handle != HCI_INVALID_HANDLE)) {
            l2c_link_hci_disc_comp (p_lcb->handle, (UINT8) - 1);
        }
    }
#if (BLE_INCLUDED == TRUE)
    l2cb.is_ble_connecting = FALSE;
#endif
}