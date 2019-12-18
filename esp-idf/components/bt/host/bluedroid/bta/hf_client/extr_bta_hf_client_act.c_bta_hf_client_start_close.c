#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;
struct TYPE_3__ {scalar_t__ sco_state; int /*<<< orphan*/  sco_close_rfc; int /*<<< orphan*/  peer_addr; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 scalar_t__ BTA_HF_CLIENT_SCO_OPEN_ST ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  L2CA_SetIdleTimeoutByBdAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_dm_pm_active (int /*<<< orphan*/ ) ; 
 TYPE_2__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_rfc_do_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_hf_client_sco_shutdown (int /*<<< orphan*/ *) ; 

void bta_hf_client_start_close(tBTA_HF_CLIENT_DATA *p_data)
{
    /* Take the link out of sniff and set L2C idle time to 0 */
#if (BTA_DM_PM_INCLUDED == TRUE)
    bta_dm_pm_active(bta_hf_client_cb.scb.peer_addr);
#endif /* (BTA_DM_PM_INCLUDED == TRUE) */
    L2CA_SetIdleTimeoutByBdAddr(bta_hf_client_cb.scb.peer_addr, 0, BT_TRANSPORT_BR_EDR);

    /* if SCO is open close SCO and wait on RFCOMM close */
    if (bta_hf_client_cb.scb.sco_state == BTA_HF_CLIENT_SCO_OPEN_ST) {
        bta_hf_client_cb.scb.sco_close_rfc = TRUE;
    } else {
        bta_hf_client_rfc_do_close(p_data);
    }

    /* always do SCO shutdown to handle all SCO corner cases */
    bta_hf_client_sco_shutdown(NULL);
}