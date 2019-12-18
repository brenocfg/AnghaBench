#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/  link_state; scalar_t__ is_bonding; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_12__ {int clock_offset; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
struct TYPE_10__ {scalar_t__ page_scan_rep_mode; scalar_t__ page_scan_mode; scalar_t__ clock_offset; } ;
struct TYPE_13__ {TYPE_1__ results; } ;
typedef  TYPE_4__ tBTM_INQ_INFO ;
typedef  scalar_t__ UINT8 ;
typedef  int UINT16 ;
struct TYPE_14__ {int /*<<< orphan*/  disallow_switch; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLI_PAGE_EVT ; 
 int BTM_GetNumAclLinks () ; 
 TYPE_4__* BTM_InqDbRead (int /*<<< orphan*/ ) ; 
 scalar_t__* BTM_ReadLocalFeatures () ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HCI_CR_CONN_ALLOW_SWITCH ; 
 scalar_t__ HCI_CR_CONN_NOT_ALLOW_SWITCH ; 
 scalar_t__ HCI_MANDATARY_PAGE_SCAN_MODE ; 
 scalar_t__ HCI_PAGE_SCAN_REP_MODE_R1 ; 
 int HCI_PKT_TYPES_MASK_DH1 ; 
 int HCI_PKT_TYPES_MASK_DH3 ; 
 int HCI_PKT_TYPES_MASK_DH5 ; 
 int HCI_PKT_TYPES_MASK_DM1 ; 
 int HCI_PKT_TYPES_MASK_DM3 ; 
 int HCI_PKT_TYPES_MASK_DM5 ; 
 scalar_t__ HCI_SWITCH_SUPPORTED (scalar_t__*) ; 
 int /*<<< orphan*/  L2CAP_LINK_CONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  LST_CONNECTING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_acl_update_busy_level (int /*<<< orphan*/ ) ; 
 TYPE_3__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_create_conn (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ l2cb ; 
 scalar_t__ l2cu_get_num_hi_priority () ; 
 int /*<<< orphan*/  l2cu_release_lcb (TYPE_2__*) ; 

BOOLEAN l2cu_create_conn_after_switch (tL2C_LCB *p_lcb)
{
    UINT8            allow_switch = HCI_CR_CONN_ALLOW_SWITCH;
    tBTM_INQ_INFO    *p_inq_info;
    UINT8            page_scan_rep_mode;
    UINT8            page_scan_mode;
    UINT16           clock_offset;
    UINT8            *p_features;
    UINT16           num_acl = BTM_GetNumAclLinks();
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev (p_lcb->remote_bd_addr);
    UINT8            no_hi_prio_chs = l2cu_get_num_hi_priority();

    p_features = BTM_ReadLocalFeatures();

    L2CAP_TRACE_DEBUG ("l2cu_create_conn_after_switch :%d num_acl:%d no_hi: %d is_bonding:%d",
                       l2cb.disallow_switch, num_acl, no_hi_prio_chs, p_lcb->is_bonding);
    /* FW team says that we can participant in 4 piconets
     * typically 3 piconet + 1 for scanning.
     * We can enhance the code to count the number of piconets later. */
    if ( ((!l2cb.disallow_switch && (num_acl < 3)) || (p_lcb->is_bonding && (no_hi_prio_chs == 0)))
            && HCI_SWITCH_SUPPORTED(p_features)) {
        allow_switch = HCI_CR_CONN_ALLOW_SWITCH;
    } else {
        allow_switch = HCI_CR_CONN_NOT_ALLOW_SWITCH;
    }

    p_lcb->link_state = LST_CONNECTING;

    /* Check with the BT manager if details about remote device are known */
    if ((p_inq_info = BTM_InqDbRead(p_lcb->remote_bd_addr)) != NULL) {
        page_scan_rep_mode = p_inq_info->results.page_scan_rep_mode;
        page_scan_mode = p_inq_info->results.page_scan_mode;
        clock_offset = (UINT16)(p_inq_info->results.clock_offset);
    } else {
        /* No info known. Use default settings */
        page_scan_rep_mode = HCI_PAGE_SCAN_REP_MODE_R1;
        page_scan_mode = HCI_MANDATARY_PAGE_SCAN_MODE;

        clock_offset = (p_dev_rec) ? p_dev_rec->clock_offset : 0;
    }

    if (!btsnd_hcic_create_conn (p_lcb->remote_bd_addr,
                                 ( HCI_PKT_TYPES_MASK_DM1 | HCI_PKT_TYPES_MASK_DH1
                                   | HCI_PKT_TYPES_MASK_DM3 | HCI_PKT_TYPES_MASK_DH3
                                   | HCI_PKT_TYPES_MASK_DM5 | HCI_PKT_TYPES_MASK_DH5 ),
                                 page_scan_rep_mode,
                                 page_scan_mode,
                                 clock_offset,
                                 allow_switch))

    {
        L2CAP_TRACE_ERROR ("L2CAP - no buffer for l2cu_create_conn");
        l2cu_release_lcb (p_lcb);
        return (FALSE);
    }

    btm_acl_update_busy_level (BTM_BLI_PAGE_EVT);

    btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK,
                     L2CAP_LINK_CONNECT_TOUT);

    return (TRUE);
}