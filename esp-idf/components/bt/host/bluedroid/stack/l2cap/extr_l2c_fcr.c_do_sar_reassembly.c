#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ rx_sdu_len; TYPE_6__* p_rx_sdu; } ;
typedef  TYPE_4__ tL2C_FCRB ;
struct TYPE_14__ {int /*<<< orphan*/  user_rx_buf_size; } ;
struct TYPE_18__ {scalar_t__ max_rx_mtu; scalar_t__ local_cid; TYPE_3__* p_lcb; TYPE_1__ ertm_info; TYPE_4__ fcrb; } ;
typedef  TYPE_5__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_20__ {TYPE_2__* fixed_reg; } ;
struct TYPE_19__ {scalar_t__ len; int offset; } ;
struct TYPE_16__ {int /*<<< orphan*/  remote_bd_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* pL2CA_FixedData_Cb ) (scalar_t__,int /*<<< orphan*/ ,TYPE_6__*) ;} ;
typedef  TYPE_6__ BT_HDR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ L2CAP_BASE_APPL_CID ; 
 scalar_t__ L2CAP_FCR_END_SDU ; 
 scalar_t__ L2CAP_FCR_SEG_BITS ; 
 scalar_t__ L2CAP_FCR_START_SDU ; 
 scalar_t__ L2CAP_FCR_UNSEG_SDU ; 
 scalar_t__ L2CAP_FIRST_FIXED_CHNL ; 
 scalar_t__ L2CAP_LAST_FIXED_CHNL ; 
 int /*<<< orphan*/  L2CAP_MAX_BUF_SIZE ; 
 scalar_t__ L2CAP_SDU_LEN_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,...) ; 
 int /*<<< orphan*/  L2CEVT_L2CAP_DATA ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_9__ l2cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  osi_free (TYPE_6__*) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static BOOLEAN do_sar_reassembly (tL2C_CCB *p_ccb, BT_HDR *p_buf, UINT16 ctrl_word)
{
    assert(p_ccb != NULL);
    assert(p_buf != NULL);

    tL2C_FCRB   *p_fcrb = &p_ccb->fcrb;
    UINT16      sar_type = ctrl_word & L2CAP_FCR_SEG_BITS;
    BOOLEAN     packet_ok = TRUE;
    UINT8       *p;

    /* Check if the SAR state is correct */
    if ((sar_type == L2CAP_FCR_UNSEG_SDU) || (sar_type == L2CAP_FCR_START_SDU)) {
        if (p_fcrb->p_rx_sdu != NULL) {
            L2CAP_TRACE_WARNING ("SAR - got unexpected unsegmented or start SDU  Expected len: %u  Got so far: %u",
                                 p_fcrb->rx_sdu_len, p_fcrb->p_rx_sdu->len);

            packet_ok = FALSE;
        }
        /* Check the length of the packet */
        if ( (sar_type == L2CAP_FCR_START_SDU) && (p_buf->len < L2CAP_SDU_LEN_OVERHEAD) ) {
            L2CAP_TRACE_WARNING ("SAR start packet too short: %u", p_buf->len);
            packet_ok = FALSE;
        }
    } else {
        if (p_fcrb->p_rx_sdu == NULL) {
            L2CAP_TRACE_WARNING ("SAR - got unexpected cont or end SDU");
            packet_ok = FALSE;
        }
    }

    if ( (packet_ok) && (sar_type != L2CAP_FCR_UNSEG_SDU) ) {
        p = ((UINT8 *)(p_buf + 1)) + p_buf->offset;

        /* For start SDU packet, extract the SDU length */
        if (sar_type == L2CAP_FCR_START_SDU) {
            /* Get the SDU length */
            STREAM_TO_UINT16 (p_fcrb->rx_sdu_len, p);
            p_buf->offset += 2;
            p_buf->len    -= 2;

            if (p_fcrb->rx_sdu_len > p_ccb->max_rx_mtu) {
                L2CAP_TRACE_WARNING ("SAR - SDU len: %u  larger than MTU: %u", p_fcrb->rx_sdu_len, p_fcrb->rx_sdu_len);
                packet_ok = FALSE;
            } else if ((p_fcrb->p_rx_sdu = (BT_HDR *)osi_malloc(L2CAP_MAX_BUF_SIZE)) == NULL) {
                L2CAP_TRACE_ERROR ("SAR - no buffer for SDU start user_rx_buf_size:%d", p_ccb->ertm_info.user_rx_buf_size);
                packet_ok = FALSE;
            } else {
                p_fcrb->p_rx_sdu->offset = 4; /* this is the minimal offset required by OBX to process incoming packets */
                p_fcrb->p_rx_sdu->len    = 0;
            }
        }

        if (packet_ok) {
            if ((p_fcrb->p_rx_sdu->len + p_buf->len) > p_fcrb->rx_sdu_len) {
                L2CAP_TRACE_ERROR ("SAR - SDU len exceeded  Type: %u   Lengths: %u %u %u",
                                   sar_type, p_fcrb->p_rx_sdu->len, p_buf->len, p_fcrb->rx_sdu_len);
                packet_ok = FALSE;
            } else if ( (sar_type == L2CAP_FCR_END_SDU) && ((p_fcrb->p_rx_sdu->len + p_buf->len) != p_fcrb->rx_sdu_len) ) {
                L2CAP_TRACE_WARNING ("SAR - SDU end rcvd but SDU incomplete: %u %u %u",
                                     p_fcrb->p_rx_sdu->len, p_buf->len, p_fcrb->rx_sdu_len);
                packet_ok = FALSE;
            } else {
                memcpy (((UINT8 *) (p_fcrb->p_rx_sdu + 1)) + p_fcrb->p_rx_sdu->offset + p_fcrb->p_rx_sdu->len, p, p_buf->len);

                p_fcrb->p_rx_sdu->len += p_buf->len;

                osi_free (p_buf);
                p_buf = NULL;

                if (sar_type == L2CAP_FCR_END_SDU) {
                    p_buf            = p_fcrb->p_rx_sdu;
                    p_fcrb->p_rx_sdu = NULL;
                }
            }
        }
    }

    if (packet_ok == FALSE) {
        osi_free (p_buf);
    } else if (p_buf != NULL) {
#if (L2CAP_NUM_FIXED_CHNLS > 0)
        if (p_ccb->local_cid < L2CAP_BASE_APPL_CID &&
                (p_ccb->local_cid >= L2CAP_FIRST_FIXED_CHNL && p_ccb->local_cid <= L2CAP_LAST_FIXED_CHNL)) {
            if (l2cb.fixed_reg[p_ccb->local_cid - L2CAP_FIRST_FIXED_CHNL].pL2CA_FixedData_Cb)
                (*l2cb.fixed_reg[p_ccb->local_cid - L2CAP_FIRST_FIXED_CHNL].pL2CA_FixedData_Cb)
                (p_ccb->local_cid, p_ccb->p_lcb->remote_bd_addr, p_buf);
        } else
#endif
        {
            l2c_csm_execute (p_ccb, L2CEVT_L2CAP_DATA, p_buf);
        }
    }

    return (packet_ok);
}