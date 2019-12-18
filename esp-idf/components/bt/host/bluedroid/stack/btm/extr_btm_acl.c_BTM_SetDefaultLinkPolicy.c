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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_2__ {int btm_def_link_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BTM_ReadLocalFeatures () ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int) ; 
 int HCI_ENABLE_HOLD_MODE ; 
 int HCI_ENABLE_MASTER_SLAVE_SWITCH ; 
 int HCI_ENABLE_PARK_MODE ; 
 int HCI_ENABLE_SNIFF_MODE ; 
 int /*<<< orphan*/  HCI_HOLD_MODE_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_PARK_MODE_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_SNIFF_MODE_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_SWITCH_SUPPORTED (int /*<<< orphan*/ *) ; 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_write_def_policy_set (int) ; 

void BTM_SetDefaultLinkPolicy (UINT16 settings)
{
    UINT8 *localFeatures = BTM_ReadLocalFeatures();

    BTM_TRACE_DEBUG("BTM_SetDefaultLinkPolicy setting:0x%04x\n", settings);

    if ((settings & HCI_ENABLE_MASTER_SLAVE_SWITCH) && (!HCI_SWITCH_SUPPORTED(localFeatures))) {
        settings &= ~HCI_ENABLE_MASTER_SLAVE_SWITCH;
        BTM_TRACE_DEBUG("BTM_SetDefaultLinkPolicy switch not supported (settings: 0x%04x)\n", settings);
    }
    if ((settings & HCI_ENABLE_HOLD_MODE) && (!HCI_HOLD_MODE_SUPPORTED(localFeatures))) {
        settings &= ~HCI_ENABLE_HOLD_MODE;
        BTM_TRACE_DEBUG("BTM_SetDefaultLinkPolicy hold not supported (settings: 0x%04x)\n", settings);
    }
    if ((settings & HCI_ENABLE_SNIFF_MODE) && (!HCI_SNIFF_MODE_SUPPORTED(localFeatures))) {
        settings &= ~HCI_ENABLE_SNIFF_MODE;
        BTM_TRACE_DEBUG("BTM_SetDefaultLinkPolicy sniff not supported (settings: 0x%04x)\n", settings);
    }
    if ((settings & HCI_ENABLE_PARK_MODE) && (!HCI_PARK_MODE_SUPPORTED(localFeatures))) {
        settings &= ~HCI_ENABLE_PARK_MODE;
        BTM_TRACE_DEBUG("BTM_SetDefaultLinkPolicy park not supported (settings: 0x%04x)\n", settings);
    }
    BTM_TRACE_DEBUG("Set DefaultLinkPolicy:0x%04x\n", settings);

    btm_cb.btm_def_link_policy = settings;

    /* Set the default Link Policy of the controller */
    btsnd_hcic_write_def_policy_set(settings);
}