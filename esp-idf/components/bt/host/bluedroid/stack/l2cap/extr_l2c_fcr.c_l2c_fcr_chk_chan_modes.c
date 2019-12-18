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
struct TYPE_6__ {int /*<<< orphan*/  allowed_modes; } ;
struct TYPE_7__ {TYPE_2__ ertm_info; TYPE_1__* p_lcb; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_5__ {int peer_ext_fea; } ;

/* Variables and functions */
 int L2CAP_EXTFEA_ENH_RETRANS ; 
 int L2CAP_EXTFEA_STREAM_MODE ; 
 int /*<<< orphan*/  L2CAP_FCR_CHAN_OPT_ERTM ; 
 int /*<<< orphan*/  L2CAP_FCR_CHAN_OPT_STREAM ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

UINT8 l2c_fcr_chk_chan_modes (tL2C_CCB *p_ccb)
{
    assert(p_ccb != NULL);

    /* Remove nonbasic options that the peer does not support */
    if (!(p_ccb->p_lcb->peer_ext_fea & L2CAP_EXTFEA_ENH_RETRANS)) {
        p_ccb->ertm_info.allowed_modes &= ~L2CAP_FCR_CHAN_OPT_ERTM;
    }

    if (!(p_ccb->p_lcb->peer_ext_fea & L2CAP_EXTFEA_STREAM_MODE)) {
        p_ccb->ertm_info.allowed_modes &= ~L2CAP_FCR_CHAN_OPT_STREAM;
    }

    /* At least one type needs to be set (Basic, ERTM, STM) to continue */
    if (!p_ccb->ertm_info.allowed_modes) {
        L2CAP_TRACE_WARNING ("L2CAP - Peer does not support our desired channel types");
    }

    return (p_ccb->ertm_info.allowed_modes);
}