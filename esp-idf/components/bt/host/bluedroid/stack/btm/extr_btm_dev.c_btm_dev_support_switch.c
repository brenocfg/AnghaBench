#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int** features; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  size_t UINT8 ;
struct TYPE_5__ {scalar_t__ (* supports_master_slave_role_switch ) () ;} ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 size_t BD_FEATURES_LEN ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 scalar_t__ FALSE ; 
 size_t HCI_EXT_FEATURES_PAGE_0 ; 
 scalar_t__ HCI_SWITCH_SUPPORTED (int*) ; 
 scalar_t__ TRUE ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ btm_is_sco_active_by_bdaddr (int /*<<< orphan*/ ) ; 
 TYPE_2__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 

BOOLEAN btm_dev_support_switch (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC  *p_dev_rec;
    UINT8   xx;
    BOOLEAN feature_empty = TRUE;

#if BTM_SCO_INCLUDED == TRUE
    /* Role switch is not allowed if a SCO is up */
    if (btm_is_sco_active_by_bdaddr(bd_addr)) {
        return (FALSE);
    }
#endif
    p_dev_rec = btm_find_dev (bd_addr);
    if (p_dev_rec && controller_get_interface()->supports_master_slave_role_switch()) {
        if (HCI_SWITCH_SUPPORTED(p_dev_rec->features[HCI_EXT_FEATURES_PAGE_0])) {
            BTM_TRACE_DEBUG("btm_dev_support_switch return TRUE (feature found)\n");
            return (TRUE);
        }

        /* If the feature field is all zero, we never received them */
        for (xx = 0 ; xx < BD_FEATURES_LEN ; xx++) {
            if (p_dev_rec->features[HCI_EXT_FEATURES_PAGE_0][xx] != 0x00) {
                feature_empty = FALSE; /* at least one is != 0 */
                break;
            }
        }

        /* If we don't know peer's capabilities, assume it supports Role-switch */
        if (feature_empty) {
            BTM_TRACE_DEBUG("btm_dev_support_switch return TRUE (feature empty)\n");
            return (TRUE);
        }
    }

    BTM_TRACE_DEBUG("btm_dev_support_switch return FALSE\n");
    return (FALSE);
}