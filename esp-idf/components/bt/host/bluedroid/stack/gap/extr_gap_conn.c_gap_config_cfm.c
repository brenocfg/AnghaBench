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
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_13__ {scalar_t__ result; TYPE_1__ fcr; } ;
typedef  TYPE_4__ tL2CAP_CFG_INFO ;
struct TYPE_11__ {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {TYPE_2__ fcr; scalar_t__ fcr_present; } ;
struct TYPE_14__ {int /*<<< orphan*/  gap_handle; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_3__ cfg; int /*<<< orphan*/  con_flags; } ;
typedef  TYPE_5__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  GAP_CCB_FLAGS_MY_CFG_DONE ; 
 int /*<<< orphan*/  GAP_EVT_CONN_CLOSED ; 
 scalar_t__ L2CAP_CFG_OK ; 
 int /*<<< orphan*/  L2CAP_FCR_BASIC_MODE ; 
 int /*<<< orphan*/  gap_checks_con_flags (TYPE_5__*) ; 
 TYPE_5__* gap_find_ccb_by_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gap_release_ccb (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_config_cfm (UINT16 l2cap_cid, tL2CAP_CFG_INFO *p_cfg)
{
    tGAP_CCB    *p_ccb;

    /* Find CCB based on CID */
    if ((p_ccb = gap_find_ccb_by_cid (l2cap_cid)) == NULL) {
        return;
    }

    if (p_cfg->result == L2CAP_CFG_OK) {
        p_ccb->con_flags |= GAP_CCB_FLAGS_MY_CFG_DONE;


        if (p_ccb->cfg.fcr_present) {
            p_ccb->cfg.fcr.mode = p_cfg->fcr.mode;
        } else {
            p_ccb->cfg.fcr.mode = L2CAP_FCR_BASIC_MODE;
        }

        gap_checks_con_flags (p_ccb);
    } else {
        p_ccb->p_callback (p_ccb->gap_handle, GAP_EVT_CONN_CLOSED);
        gap_release_ccb (p_ccb);
    }
}