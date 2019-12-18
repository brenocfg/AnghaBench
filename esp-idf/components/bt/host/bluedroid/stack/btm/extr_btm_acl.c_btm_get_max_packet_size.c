#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pkt_types_mask; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  int UINT16 ;
struct TYPE_7__ {int btm_acl_pkt_types_supported; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_address ) () ;} ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_ACL_PKT_TYPES_MASK_DH1 ; 
 int BTM_ACL_PKT_TYPES_MASK_DH3 ; 
 int BTM_ACL_PKT_TYPES_MASK_DH5 ; 
 int BTM_ACL_PKT_TYPES_MASK_DM1 ; 
 int BTM_ACL_PKT_TYPES_MASK_DM3 ; 
 int BTM_ACL_PKT_TYPES_MASK_DM5 ; 
 int BTM_ACL_PKT_TYPES_MASK_NO_2_DH1 ; 
 int BTM_ACL_PKT_TYPES_MASK_NO_2_DH3 ; 
 int BTM_ACL_PKT_TYPES_MASK_NO_2_DH5 ; 
 int BTM_ACL_PKT_TYPES_MASK_NO_3_DH1 ; 
 int BTM_ACL_PKT_TYPES_MASK_NO_3_DH3 ; 
 int BTM_ACL_PKT_TYPES_MASK_NO_3_DH5 ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int HCI_DH1_PACKET_SIZE ; 
 int HCI_DH3_PACKET_SIZE ; 
 int HCI_DH5_PACKET_SIZE ; 
 int HCI_DM1_PACKET_SIZE ; 
 int HCI_DM3_PACKET_SIZE ; 
 int HCI_DM5_PACKET_SIZE ; 
 int HCI_EDR2_DH1_PACKET_SIZE ; 
 int HCI_EDR2_DH3_PACKET_SIZE ; 
 int HCI_EDR2_DH5_PACKET_SIZE ; 
 int HCI_EDR3_DH1_PACKET_SIZE ; 
 int HCI_EDR3_DH3_PACKET_SIZE ; 
 int HCI_EDR3_DH5_PACKET_SIZE ; 
 TYPE_1__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 
 TYPE_2__* controller_get_interface () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

UINT16 btm_get_max_packet_size (BD_ADDR addr)
{
    tACL_CONN   *p = btm_bda_to_acl(addr, BT_TRANSPORT_BR_EDR);
    UINT16      pkt_types = 0;
    UINT16      pkt_size = 0;
    BTM_TRACE_DEBUG ("btm_get_max_packet_size\n");
    if (p != NULL) {
        pkt_types = p->pkt_types_mask;
    } else {
        /* Special case for when info for the local device is requested */
        if (memcmp (controller_get_interface()->get_address(), addr, BD_ADDR_LEN) == 0) {
            pkt_types = btm_cb.btm_acl_pkt_types_supported;
        }
    }

    if (pkt_types) {
        if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_3_DH5)) {
            pkt_size = HCI_EDR3_DH5_PACKET_SIZE;
        } else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_2_DH5)) {
            pkt_size = HCI_EDR2_DH5_PACKET_SIZE;
        } else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_3_DH3)) {
            pkt_size = HCI_EDR3_DH3_PACKET_SIZE;
        } else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DH5) {
            pkt_size = HCI_DH5_PACKET_SIZE;
        } else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_2_DH3)) {
            pkt_size = HCI_EDR2_DH3_PACKET_SIZE;
        } else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DM5) {
            pkt_size = HCI_DM5_PACKET_SIZE;
        } else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DH3) {
            pkt_size = HCI_DH3_PACKET_SIZE;
        } else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DM3) {
            pkt_size = HCI_DM3_PACKET_SIZE;
        } else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_3_DH1)) {
            pkt_size = HCI_EDR3_DH1_PACKET_SIZE;
        } else if (!(pkt_types & BTM_ACL_PKT_TYPES_MASK_NO_2_DH1)) {
            pkt_size = HCI_EDR2_DH1_PACKET_SIZE;
        } else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DH1) {
            pkt_size = HCI_DH1_PACKET_SIZE;
        } else if (pkt_types & BTM_ACL_PKT_TYPES_MASK_DM1) {
            pkt_size = HCI_DM1_PACKET_SIZE;
        }
    }

    return (pkt_size);
}