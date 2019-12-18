#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mps; } ;
struct TYPE_8__ {TYPE_2__ fcr; } ;
struct TYPE_9__ {int tx_mps; TYPE_3__ peer_cfg; TYPE_1__* p_lcb; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int UINT16 ;
struct TYPE_6__ {int /*<<< orphan*/  remote_bd_addr; } ;

/* Variables and functions */
 int L2CAP_FCR_OVERHEAD ; 
 int L2CAP_FCS_LEN ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SDU_LEN_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int,int,...) ; 
 int btm_get_max_packet_size (int /*<<< orphan*/ ) ; 

void l2cu_adjust_out_mps (tL2C_CCB *p_ccb)
{
    UINT16 packet_size;

    /* on the tx side MTU is selected based on packet size of the controller */
    packet_size = btm_get_max_packet_size (p_ccb->p_lcb->remote_bd_addr);

    if (packet_size <= (L2CAP_PKT_OVERHEAD + L2CAP_FCR_OVERHEAD + L2CAP_SDU_LEN_OVERHEAD + L2CAP_FCS_LEN)) {
        /* something is very wrong */
        L2CAP_TRACE_DEBUG ("l2cu_adjust_out_mps bad packet size: %u  will use MPS: %u", packet_size, p_ccb->peer_cfg.fcr.mps);
        p_ccb->tx_mps = p_ccb->peer_cfg.fcr.mps;
    } else {
        packet_size -= (L2CAP_PKT_OVERHEAD + L2CAP_FCR_OVERHEAD + L2CAP_SDU_LEN_OVERHEAD + L2CAP_FCS_LEN);

        /* We try to negotiate MTU that each packet can be split into whole
        number of max packets.  For example if link is 1.2 max packet size is 339 bytes.
        At first calculate how many whole packets it is.  MAX L2CAP is 1691 + 4 overhead.
        1695, that will be 5 Dh5 packets.  Now maximum L2CAP packet is
        5 * 339 = 1695. Minus 4 bytes L2CAP header 1691.

        For EDR 2.0 packet size is 1027.  So we better send RFCOMM packet as 1 3DH5 packet
        1 * 1027 = 1027.  Minus 4 bytes L2CAP header 1023.  */
        if (p_ccb->peer_cfg.fcr.mps >= packet_size) {
            p_ccb->tx_mps = p_ccb->peer_cfg.fcr.mps / packet_size * packet_size;
        } else {
            p_ccb->tx_mps = p_ccb->peer_cfg.fcr.mps;
        }

        L2CAP_TRACE_DEBUG ("l2cu_adjust_out_mps use %d   Based on peer_cfg.fcr.mps: %u  packet_size: %u",
                           p_ccb->tx_mps, p_ccb->peer_cfg.fcr.mps, packet_size);
    }
}