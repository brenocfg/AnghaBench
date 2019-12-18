#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  qos; scalar_t__ qos_present; } ;
struct TYPE_9__ {TYPE_1__ peer_cfg; } ;
typedef  TYPE_2__ tL2C_CCB ;
struct TYPE_10__ {scalar_t__ qos_present; int /*<<< orphan*/  qos; } ;
typedef  TYPE_3__ tL2CAP_CFG_INFO ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  l2c_fcr_adj_our_rsp_options (TYPE_2__*,TYPE_3__*) ; 

void l2cu_process_our_cfg_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    /* If peer wants QoS, we are allowed to change the values in a positive response */
    if ( (p_cfg->qos_present) && (p_ccb->peer_cfg.qos_present) ) {
        p_ccb->peer_cfg.qos = p_cfg->qos;
    } else {
        p_cfg->qos_present = FALSE;
    }

    l2c_fcr_adj_our_rsp_options (p_ccb, p_cfg);
}