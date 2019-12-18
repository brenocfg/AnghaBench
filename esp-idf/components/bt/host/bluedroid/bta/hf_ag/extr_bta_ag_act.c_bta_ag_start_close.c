#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  post_sco; int /*<<< orphan*/  peer_addr; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_POST_SCO_CLOSE_RFC ; 
 int /*<<< orphan*/  BTA_AG_POST_SCO_NONE ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  L2CA_SetIdleTimeoutByBdAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_rfc_do_close (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bta_ag_sco_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  bta_ag_sco_shutdown (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_dm_pm_active (int /*<<< orphan*/ ) ; 

void bta_ag_start_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    /* Take the link out of sniff and set L2C idle time to 0 */
    bta_dm_pm_active(p_scb->peer_addr);
    L2CA_SetIdleTimeoutByBdAddr(p_scb->peer_addr, 0, BT_TRANSPORT_BR_EDR);
    /* if SCO is open close SCO and wait on RFCOMM close */
    if (bta_ag_sco_is_open(p_scb)) {
        p_scb->post_sco = BTA_AG_POST_SCO_CLOSE_RFC;
    } else {
        p_scb->post_sco = BTA_AG_POST_SCO_NONE;
        bta_ag_rfc_do_close(p_scb, p_data);
    }
    /* Always do SCO shutdown to handle all SCO corner cases */
    bta_ag_sco_shutdown(p_scb, p_data);
}