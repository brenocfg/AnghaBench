#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* peer_chnl_mask; scalar_t__ transport; int /*<<< orphan*/  disc_reason; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/ ** p_fixed_ccbs; int /*<<< orphan*/ * p_pending_ccb; } ;
typedef  TYPE_2__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2C_CCB ;
typedef  int UINT8 ;
struct TYPE_7__ {TYPE_1__* fixed_reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* pL2CA_FixedConn_Cb ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int L2CAP_FIRST_FIXED_CHNL ; 
 int L2CAP_NUM_FIXED_CHNLS ; 
 TYPE_4__ l2cb ; 
 int /*<<< orphan*/  l2cu_release_ccb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void l2cu_process_fixed_disc_cback (tL2C_LCB *p_lcb)
{
#if (L2CAP_NUM_FIXED_CHNLS > 0)

    /* Select peer channels mask to use depending on transport */
    UINT8 peer_channel_mask = p_lcb->peer_chnl_mask[0];

    // For LE, reset the stored peer channel mask
    if (p_lcb->transport == BT_TRANSPORT_LE) {
        p_lcb->peer_chnl_mask[0] = 0;
    }

    for (int xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++) {
        if (p_lcb->p_fixed_ccbs[xx]) {
            if (p_lcb->p_fixed_ccbs[xx] != p_lcb->p_pending_ccb) {
                tL2C_CCB *p_l2c_chnl_ctrl_block;
                p_l2c_chnl_ctrl_block = p_lcb->p_fixed_ccbs[xx];
                p_lcb->p_fixed_ccbs[xx] = NULL;
                l2cu_release_ccb(p_l2c_chnl_ctrl_block);
#if BLE_INCLUDED == TRUE
                (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(xx + L2CAP_FIRST_FIXED_CHNL,
                        p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason, p_lcb->transport);
#else
                (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(xx + L2CAP_FIRST_FIXED_CHNL,
                        p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason, BT_TRANSPORT_BR_EDR);
#endif
            }
        } else if ( (peer_channel_mask & (1 << (xx + L2CAP_FIRST_FIXED_CHNL)))
                    && (l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb != NULL) ) {
#if BLE_INCLUDED == TRUE
            (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(xx + L2CAP_FIRST_FIXED_CHNL,
                    p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason, p_lcb->transport);
#else
            (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(xx + L2CAP_FIRST_FIXED_CHNL,
                    p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason, BT_TRANSPORT_BR_EDR);
#endif
        }
    }
#endif
}