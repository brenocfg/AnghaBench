#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* send_f_rsp; scalar_t__ local_busy; scalar_t__ srej_sent; void* remote_busy; void* rej_sent; int /*<<< orphan*/ * s_frames_rcvd; } ;
typedef  TYPE_1__ tL2C_FCRB ;
struct TYPE_11__ {TYPE_1__ fcrb; } ;
typedef  TYPE_2__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_12__ {scalar_t__ len; } ;
typedef  TYPE_3__ BT_HDR ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 void* FALSE ; 
 size_t L2CAP_FCR_F_BIT ; 
 size_t L2CAP_FCR_P_BIT ; 
 size_t L2CAP_FCR_REQ_SEQ_BITS ; 
 size_t L2CAP_FCR_REQ_SEQ_BITS_SHIFT ; 
 size_t L2CAP_FCR_SUP_BITS ; 
#define  L2CAP_FCR_SUP_REJ 131 
#define  L2CAP_FCR_SUP_RNR 130 
#define  L2CAP_FCR_SUP_RR 129 
 size_t L2CAP_FCR_SUP_SHIFT ; 
#define  L2CAP_FCR_SUP_SREJ 128 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,scalar_t__) ; 
 int /*<<< orphan*/  L2C_FCR_RETX_ALL_PKTS ; 
 void* TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_fcr_send_S_frame (TYPE_2__*,int const,size_t) ; 
 int /*<<< orphan*/  l2c_fcr_stop_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  osi_free (TYPE_3__*) ; 
 void* retransmit_i_frames (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_s_frame (tL2C_CCB *p_ccb, BT_HDR *p_buf, UINT16 ctrl_word)
{
    assert(p_ccb != NULL);
    assert(p_buf != NULL);

    tL2C_FCRB   *p_fcrb      = &p_ccb->fcrb;
    UINT16      s_frame_type = (ctrl_word & L2CAP_FCR_SUP_BITS) >> L2CAP_FCR_SUP_SHIFT;
    BOOLEAN     remote_was_busy;
    BOOLEAN     all_ok = TRUE;

    if (p_buf->len != 0) {
        L2CAP_TRACE_WARNING ("Incorrect S-frame Length (%d)", p_buf->len);
    }

    L2CAP_TRACE_DEBUG ("process_s_frame ctrl_word 0x%04x fcrb_remote_busy:%d", ctrl_word, p_fcrb->remote_busy);

#if (L2CAP_ERTM_STATS == TRUE)
    p_ccb->fcrb.s_frames_rcvd[s_frame_type]++;
#endif

    if (ctrl_word & L2CAP_FCR_P_BIT) {
        p_fcrb->rej_sent   = FALSE;             /* After checkpoint, we can send anoher REJ */
        p_fcrb->send_f_rsp = TRUE;              /* Set a flag in case an I-frame is pending */
    }

    switch (s_frame_type) {
    case L2CAP_FCR_SUP_RR:
        remote_was_busy     = p_fcrb->remote_busy;
        p_fcrb->remote_busy = FALSE;

        if ( (ctrl_word & L2CAP_FCR_F_BIT) || (remote_was_busy) ) {
            all_ok = retransmit_i_frames (p_ccb, L2C_FCR_RETX_ALL_PKTS);
        }
        break;

    case L2CAP_FCR_SUP_REJ:
        p_fcrb->remote_busy = FALSE;
        all_ok = retransmit_i_frames (p_ccb, L2C_FCR_RETX_ALL_PKTS);
        break;

    case L2CAP_FCR_SUP_RNR:
        p_fcrb->remote_busy = TRUE;
        l2c_fcr_stop_timer (p_ccb);
        break;

    case L2CAP_FCR_SUP_SREJ:
        p_fcrb->remote_busy = FALSE;
        all_ok = retransmit_i_frames (p_ccb, (UINT8)((ctrl_word & L2CAP_FCR_REQ_SEQ_BITS) >> L2CAP_FCR_REQ_SEQ_BITS_SHIFT));
        break;
    }

    if (all_ok) {
        /* If polled, we need to respond with F-bit. Note, we may have sent a I-frame with the F-bit */
        if (p_fcrb->send_f_rsp) {
            if (p_fcrb->srej_sent) {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_SREJ, L2CAP_FCR_F_BIT);
            } else if (p_fcrb->local_busy) {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RNR, L2CAP_FCR_F_BIT);
            } else {
                l2c_fcr_send_S_frame (p_ccb, L2CAP_FCR_SUP_RR, L2CAP_FCR_F_BIT);
            }

            p_fcrb->send_f_rsp = FALSE;
        }
    } else {
        L2CAP_TRACE_DEBUG ("process_s_frame hit_max_retries");
    }

    osi_free (p_buf);
}