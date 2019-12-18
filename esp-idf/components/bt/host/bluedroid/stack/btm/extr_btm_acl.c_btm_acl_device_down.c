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
struct TYPE_3__ {int /*<<< orphan*/  hci_handle; scalar_t__ in_use; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_1__* acl_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  HCI_ERR_HW_FAILURE ; 
 scalar_t__ MAX_L2CAP_LINKS ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  l2c_link_hci_disc_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_acl_device_down (void)
{
    tACL_CONN   *p = &btm_cb.acl_db[0];
    UINT16      xx;
    BTM_TRACE_DEBUG ("btm_acl_device_down\n");
    for (xx = 0; xx < MAX_L2CAP_LINKS; xx++, p++) {
        if (p->in_use) {
            BTM_TRACE_DEBUG ("hci_handle=%d HCI_ERR_HW_FAILURE \n", p->hci_handle );
            l2c_link_hci_disc_comp (p->hci_handle, HCI_ERR_HW_FAILURE);
        }
    }
}