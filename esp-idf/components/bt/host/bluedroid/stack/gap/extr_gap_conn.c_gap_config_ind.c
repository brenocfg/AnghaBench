#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ mtu; void* fcs_present; int /*<<< orphan*/  result; void* mtu_present; void* flush_to_present; } ;
typedef  TYPE_4__ tL2CAP_CFG_INFO ;
struct TYPE_12__ {int user_tx_buf_size; } ;
struct TYPE_10__ {scalar_t__ mode; } ;
struct TYPE_11__ {TYPE_1__ fcr; } ;
struct TYPE_14__ {scalar_t__ rem_mtu_size; int /*<<< orphan*/  con_flags; TYPE_3__ ertm_info; TYPE_2__ cfg; } ;
typedef  TYPE_5__ tGAP_CCB ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GAP_CCB_FLAGS_HIS_CFG_DONE ; 
 int /*<<< orphan*/  L2CAP_CFG_OK ; 
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 int L2CAP_MIN_OFFSET ; 
 scalar_t__ L2CAP_MTU_SIZE ; 
 int /*<<< orphan*/  L2CA_CONFIG_RSP (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  gap_checks_con_flags (TYPE_5__*) ; 
 TYPE_5__* gap_find_ccb_by_cid (scalar_t__) ; 

__attribute__((used)) static void gap_config_ind (UINT16 l2cap_cid, tL2CAP_CFG_INFO *p_cfg)
{
    tGAP_CCB    *p_ccb;
    UINT16      local_mtu_size;

    /* Find CCB based on CID */
    if ((p_ccb = gap_find_ccb_by_cid (l2cap_cid)) == NULL) {
        return;
    }

    /* Remember the remote MTU size */

    if (p_ccb->cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) {
        local_mtu_size = p_ccb->ertm_info.user_tx_buf_size
                         - sizeof(BT_HDR) - L2CAP_MIN_OFFSET;
    } else {
        local_mtu_size = L2CAP_MTU_SIZE;
    }

    if ((!p_cfg->mtu_present) || (p_cfg->mtu > local_mtu_size)) {
        p_ccb->rem_mtu_size = local_mtu_size;
    } else {
        p_ccb->rem_mtu_size = p_cfg->mtu;
    }

    /* For now, always accept configuration from the other side */
    p_cfg->flush_to_present = FALSE;
    p_cfg->mtu_present      = FALSE;
    p_cfg->result           = L2CAP_CFG_OK;
    p_cfg->fcs_present      = FALSE;

    L2CA_CONFIG_RSP (l2cap_cid, p_cfg);

    p_ccb->con_flags |= GAP_CCB_FLAGS_HIS_CFG_DONE;

    gap_checks_con_flags (p_ccb);
}