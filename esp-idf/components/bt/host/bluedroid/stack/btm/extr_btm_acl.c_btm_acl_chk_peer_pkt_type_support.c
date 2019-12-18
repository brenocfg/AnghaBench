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
struct TYPE_3__ {int /*<<< orphan*/ * peer_lmp_features; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_DH3 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_DH5 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_DM3 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_DM5 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_NO_2_DH1 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_NO_2_DH5 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_NO_3_DH1 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_NO_3_DH3 ; 
 int /*<<< orphan*/  BTM_ACL_PKT_TYPES_MASK_NO_3_DH5 ; 
 int /*<<< orphan*/  HCI_3_SLOT_EDR_ACL_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_3_SLOT_PACKETS_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_5_SLOT_EDR_ACL_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_5_SLOT_PACKETS_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_EDR_ACL_2MPS_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_EDR_ACL_3MPS_SUPPORTED (int /*<<< orphan*/ ) ; 
 size_t HCI_EXT_FEATURES_PAGE_0 ; 

void btm_acl_chk_peer_pkt_type_support (tACL_CONN *p, UINT16 *p_pkt_type)
{
    /* 3 and 5 slot packets? */
    if (!HCI_3_SLOT_PACKETS_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0])) {
        *p_pkt_type &= ~(BTM_ACL_PKT_TYPES_MASK_DH3 + BTM_ACL_PKT_TYPES_MASK_DM3);
    }

    if (!HCI_5_SLOT_PACKETS_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0])) {
        *p_pkt_type &= ~(BTM_ACL_PKT_TYPES_MASK_DH5 + BTM_ACL_PKT_TYPES_MASK_DM5);
    }

    /* 2 and 3 MPS support? */
    if (!HCI_EDR_ACL_2MPS_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0])) {
        /* Not supported. Add 'not_supported' mask for all 2MPS packet types */
        *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_2_DH1 + BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 +
                        BTM_ACL_PKT_TYPES_MASK_NO_2_DH5);
    }

    if (!HCI_EDR_ACL_3MPS_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0])) {
        /* Not supported. Add 'not_supported' mask for all 3MPS packet types */
        *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_3_DH1 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH3 +
                        BTM_ACL_PKT_TYPES_MASK_NO_3_DH5);
    }

    /* EDR 3 and 5 slot support? */
    if (HCI_EDR_ACL_2MPS_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0])
            || HCI_EDR_ACL_3MPS_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0])) {
        if (!HCI_3_SLOT_EDR_ACL_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0]))
            /* Not supported. Add 'not_supported' mask for all 3-slot EDR packet types */
        {
            *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH3);
        }

        if (!HCI_5_SLOT_EDR_ACL_SUPPORTED(p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0]))
            /* Not supported. Add 'not_supported' mask for all 5-slot EDR packet types */
        {
            *p_pkt_type |= (BTM_ACL_PKT_TYPES_MASK_NO_2_DH5 + BTM_ACL_PKT_TYPES_MASK_NO_3_DH5);
        }
    }
}