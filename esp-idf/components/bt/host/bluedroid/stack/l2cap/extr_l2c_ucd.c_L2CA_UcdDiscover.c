#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_1__ ucd; } ;
typedef  TYPE_2__ tL2C_RCB ;
struct TYPE_9__ {scalar_t__ link_state; } ;
typedef  TYPE_3__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2C_CCB ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  scalar_t__ BOOLEAN ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  L2CAP_CONNECTIONLESS_CID ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 int L2CAP_UCD_INFO_TYPE_MTU ; 
 int L2CAP_UCD_INFO_TYPE_RECEPTION ; 
 int /*<<< orphan*/  L2C_UCD_STATE_UNUSED ; 
 int /*<<< orphan*/  L2C_UCD_STATE_W4_MTU ; 
 int /*<<< orphan*/  L2C_UCD_STATE_W4_RECEPTION ; 
 scalar_t__ LST_CONNECTED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  l2c_ucd_check_pending_info_req (int /*<<< orphan*/ *) ; 
 scalar_t__ l2c_ucd_connect (int*) ; 
 int /*<<< orphan*/ * l2cu_find_ccb_by_cid (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* l2cu_find_lcb_by_bd_addr (int*,int /*<<< orphan*/ ) ; 
 TYPE_2__* l2cu_find_rcb_by_psm (int /*<<< orphan*/ ) ; 

BOOLEAN L2CA_UcdDiscover ( UINT16 psm, BD_ADDR rem_bda, UINT8 info_type )
{
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;
    tL2C_RCB        *p_rcb;

    L2CAP_TRACE_API ("L2CA_UcdDiscover()  PSM: 0x%04x  BDA: %08x%04x, InfoType=0x%02x", psm,
                     (rem_bda[0] << 24) + (rem_bda[1] << 16) + (rem_bda[2] << 8) + rem_bda[3],
                     (rem_bda[4] << 8) + rem_bda[5], info_type);

    /* Fail if the PSM is not registered */
    if (((p_rcb = l2cu_find_rcb_by_psm (psm)) == NULL)
            || ( p_rcb->ucd.state == L2C_UCD_STATE_UNUSED )) {
        L2CAP_TRACE_WARNING ("L2CAP - no RCB for L2CA_UcdDiscover, PSM: 0x%04x", psm);
        return (FALSE);
    }

    /* First, see if we already have a link to the remote */
    /* then find the channel control block for UCD. */
    if (((p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda, BT_TRANSPORT_BR_EDR)) == NULL)
            || ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, L2CAP_CONNECTIONLESS_CID)) == NULL)) {
        if ( l2c_ucd_connect (rem_bda) == FALSE ) {
            return (FALSE);
        }
    }

    /* set waiting flags in rcb */

    if ( info_type & L2CAP_UCD_INFO_TYPE_RECEPTION ) {
        p_rcb->ucd.state |= L2C_UCD_STATE_W4_RECEPTION;
    }

    if ( info_type & L2CAP_UCD_INFO_TYPE_MTU ) {
        p_rcb->ucd.state |= L2C_UCD_STATE_W4_MTU;
    }

    /* if link is already established */
    if ((p_lcb) && (p_lcb->link_state == LST_CONNECTED)) {
        if (!p_ccb) {
            p_ccb = l2cu_find_ccb_by_cid (p_lcb, L2CAP_CONNECTIONLESS_CID);
        }
        l2c_ucd_check_pending_info_req(p_ccb);
    }
    return (TRUE);
}