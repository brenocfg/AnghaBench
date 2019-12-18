#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ link_state; TYPE_8__** p_fixed_ccbs; int /*<<< orphan*/  timer_entry; } ;
typedef  TYPE_7__ tL2C_LCB ;
struct TYPE_19__ {int max_held_acks; } ;
struct TYPE_18__ {int /*<<< orphan*/  user_tx_buf_size; int /*<<< orphan*/  user_rx_buf_size; int /*<<< orphan*/  fcr_tx_buf_size; int /*<<< orphan*/  fcr_rx_buf_size; } ;
struct TYPE_23__ {int tx_win_sz; } ;
struct TYPE_17__ {TYPE_9__ fcr; } ;
struct TYPE_16__ {TYPE_9__ fcr; } ;
struct TYPE_15__ {scalar_t__ param; } ;
struct TYPE_22__ {size_t local_cid; size_t remote_cid; int /*<<< orphan*/  fixed_chnl_idle_tout; int /*<<< orphan*/  chnl_state; TYPE_7__* p_lcb; TYPE_5__ fcrb; TYPE_4__ ertm_info; TYPE_3__ peer_cfg; TYPE_2__ our_cfg; TYPE_1__ timer_entry; int /*<<< orphan*/  is_flushable; } ;
typedef  TYPE_8__ tL2C_CCB ;
typedef  TYPE_9__ tL2CAP_FCR_OPTS ;
typedef  size_t UINT16 ;
struct TYPE_20__ {int /*<<< orphan*/  default_idle_tout; } ;
struct TYPE_14__ {TYPE_6__* fixed_reg; } ;
typedef  scalar_t__ TIMER_PARAM_TYPE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CST_OPEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_FCR_RX_BUF_SIZE ; 
 int /*<<< orphan*/  L2CAP_FCR_TX_BUF_SIZE ; 
 size_t L2CAP_FIRST_FIXED_CHNL ; 
 int /*<<< orphan*/  L2CAP_USER_RX_BUF_SIZE ; 
 int /*<<< orphan*/  L2CAP_USER_TX_BUF_SIZE ; 
 scalar_t__ LST_CONNECTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 TYPE_13__ l2cb ; 
 TYPE_8__* l2cu_allocate_ccb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN l2cu_initialize_fixed_ccb (tL2C_LCB *p_lcb, UINT16 fixed_cid, tL2CAP_FCR_OPTS *p_fcr)
{
#if (L2CAP_NUM_FIXED_CHNLS > 0)
    tL2C_CCB    *p_ccb;
    /* If we already have a CCB, then simply return */
    if (p_lcb->p_fixed_ccbs[fixed_cid - L2CAP_FIRST_FIXED_CHNL] != NULL) {
        return (TRUE);
    }

    if ((p_ccb = l2cu_allocate_ccb (NULL, 0)) == NULL) {
        return (FALSE);
    }

    btu_stop_timer(&p_lcb->timer_entry);

    /* Set CID for the connection */
    p_ccb->local_cid  = fixed_cid;
    p_ccb->remote_cid = fixed_cid;

    p_ccb->is_flushable = FALSE;

    p_ccb->timer_entry.param  = (TIMER_PARAM_TYPE)p_ccb;


    if (p_fcr) {
        /* Set the FCR parameters. For now, we will use default pools */
        p_ccb->our_cfg.fcr = p_ccb->peer_cfg.fcr = *p_fcr;

        p_ccb->ertm_info.fcr_rx_buf_size  = L2CAP_FCR_RX_BUF_SIZE;
        p_ccb->ertm_info.fcr_tx_buf_size  = L2CAP_FCR_TX_BUF_SIZE;
        p_ccb->ertm_info.user_rx_buf_size = L2CAP_USER_RX_BUF_SIZE;
        p_ccb->ertm_info.user_tx_buf_size = L2CAP_USER_TX_BUF_SIZE;

        p_ccb->fcrb.max_held_acks = p_fcr->tx_win_sz / 3;
    }

    /* Link ccb to lcb and lcb to ccb */
    p_lcb->p_fixed_ccbs[fixed_cid - L2CAP_FIRST_FIXED_CHNL] = p_ccb;
    p_ccb->p_lcb = p_lcb;

    /* There is no configuration, so if the link is up, the channel is up */
    if (p_lcb->link_state == LST_CONNECTED) {
        p_ccb->chnl_state = CST_OPEN;
    }

    /* Set the default idle timeout value to use */
    p_ccb->fixed_chnl_idle_tout = l2cb.fixed_reg[fixed_cid - L2CAP_FIRST_FIXED_CHNL].default_idle_tout;
#endif
    return (TRUE);
}