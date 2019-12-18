#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tL2CAP_CFG_INFO ;
struct TYPE_3__ {scalar_t__ con_state; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_PASS ; 
 scalar_t__ GAP_CCB_STATE_CONNECTED ; 
 int /*<<< orphan*/  GAP_ERR_BAD_HANDLE ; 
 int /*<<< orphan*/  L2CA_CONFIG_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* gap_find_ccb_by_handle (int /*<<< orphan*/ ) ; 

UINT16 GAP_ConnReconfig (UINT16 gap_handle, tL2CAP_CFG_INFO *p_cfg)
{
    tGAP_CCB    *p_ccb = gap_find_ccb_by_handle (gap_handle);

    if (!p_ccb) {
        return (GAP_ERR_BAD_HANDLE);
    }

    p_ccb->cfg = *p_cfg;

    if (p_ccb->con_state == GAP_CCB_STATE_CONNECTED) {
        L2CA_CONFIG_REQ (p_ccb->connection_id, p_cfg);
    }

    return (BT_PASS);
}