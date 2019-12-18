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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {int /*<<< orphan*/  hci_handle; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/ * BTM_ReadLocalFeatures () ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int HCI_DISABLE_ALL_LM_MODES ; 
 int HCI_ENABLE_HOLD_MODE ; 
 int HCI_ENABLE_MASTER_SLAVE_SWITCH ; 
 int HCI_ENABLE_PARK_MODE ; 
 int HCI_ENABLE_SNIFF_MODE ; 
 int /*<<< orphan*/  HCI_HOLD_MODE_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_PARK_MODE_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_SNIFF_MODE_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_SWITCH_SUPPORTED (int /*<<< orphan*/ *) ; 
 TYPE_1__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btsnd_hcic_write_policy_set (int /*<<< orphan*/ ,int) ; 

tBTM_STATUS BTM_SetLinkPolicy (BD_ADDR remote_bda, UINT16 *settings)
{
    tACL_CONN   *p;
    UINT8       *localFeatures = BTM_ReadLocalFeatures();
    BTM_TRACE_DEBUG ("BTM_SetLinkPolicy\n");
    /*    BTM_TRACE_API ("BTM_SetLinkPolicy: requested settings: 0x%04x", *settings ); */

    /* First, check if hold mode is supported */
    if (*settings != HCI_DISABLE_ALL_LM_MODES) {
        if ( (*settings & HCI_ENABLE_MASTER_SLAVE_SWITCH) && (!HCI_SWITCH_SUPPORTED(localFeatures)) ) {
            *settings &= (~HCI_ENABLE_MASTER_SLAVE_SWITCH);
            BTM_TRACE_API ("BTM_SetLinkPolicy switch not supported (settings: 0x%04x)\n", *settings );
        }
        if ( (*settings & HCI_ENABLE_HOLD_MODE) && (!HCI_HOLD_MODE_SUPPORTED(localFeatures)) ) {
            *settings &= (~HCI_ENABLE_HOLD_MODE);
            BTM_TRACE_API ("BTM_SetLinkPolicy hold not supported (settings: 0x%04x)\n", *settings );
        }
        if ( (*settings & HCI_ENABLE_SNIFF_MODE) && (!HCI_SNIFF_MODE_SUPPORTED(localFeatures)) ) {
            *settings &= (~HCI_ENABLE_SNIFF_MODE);
            BTM_TRACE_API ("BTM_SetLinkPolicy sniff not supported (settings: 0x%04x)\n", *settings );
        }
        if ( (*settings & HCI_ENABLE_PARK_MODE) && (!HCI_PARK_MODE_SUPPORTED(localFeatures)) ) {
            *settings &= (~HCI_ENABLE_PARK_MODE);
            BTM_TRACE_API ("BTM_SetLinkPolicy park not supported (settings: 0x%04x)\n", *settings );
        }
    }

    if ((p = btm_bda_to_acl(remote_bda, BT_TRANSPORT_BR_EDR)) != NULL) {
        return (btsnd_hcic_write_policy_set (p->hci_handle, *settings) ? BTM_CMD_STARTED : BTM_NO_RESOURCES);
    }

    /* If here, no BD Addr found */
    return (BTM_UNKNOWN_ADDR);
}