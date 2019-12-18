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
struct TYPE_3__ {int /*<<< orphan*/  peer_bda; int /*<<< orphan*/  transport; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_CONN_TERMINATE_LOCAL_HOST ; 
 int /*<<< orphan*/  GATT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  L2CA_GetDisconnectReason (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ btm_sec_is_a_bonded_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_add_a_bonded_dev_for_srv_chg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_cleanup_upon_disc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gatt_find_tcb_by_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gatt_is_bda_in_the_srv_chg_clt_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gatt_l2cif_disconnect_cfm_cback(UINT16 lcid, UINT16 result)
{
    tGATT_TCB       *p_tcb;
    UINT16          reason;
    UNUSED(result);

    /* look up clcb for this channel */
    if ((p_tcb = gatt_find_tcb_by_cid(lcid)) != NULL) {
        /* If the device is not in the service changed client list, add it... */
        if (gatt_is_bda_in_the_srv_chg_clt_list(p_tcb->peer_bda) == NULL) {
            if (btm_sec_is_a_bonded_dev(p_tcb->peer_bda)) {
                gatt_add_a_bonded_dev_for_srv_chg(p_tcb->peer_bda);
            }
        }

        /* send disconnect callback */
        /* if ACL link is still up, no reason is logged, l2cap is disconnect from peer */
        if ((reason = L2CA_GetDisconnectReason(p_tcb->peer_bda, p_tcb->transport)) == 0) {
            reason = GATT_CONN_TERMINATE_LOCAL_HOST;
        }

        gatt_cleanup_upon_disc(p_tcb->peer_bda, reason, GATT_TRANSPORT_BR_EDR);
    }
}