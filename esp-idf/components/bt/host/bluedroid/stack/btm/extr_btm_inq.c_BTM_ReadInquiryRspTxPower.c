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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_3__ {int /*<<< orphan*/  txpwer_timer; int /*<<< orphan*/ * p_txpwer_cmpl_cb; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BUSY ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_INQ_REPLY_TIMEOUT ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_ACL ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_read_inq_tx_power () ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 

tBTM_STATUS BTM_ReadInquiryRspTxPower (tBTM_CMPL_CB *p_cb)
{
    if (btm_cb.devcb.p_txpwer_cmpl_cb) {
        return (BTM_BUSY);
    }

    btu_start_timer (&btm_cb.devcb.txpwer_timer, BTU_TTYPE_BTM_ACL, BTM_INQ_REPLY_TIMEOUT );


    btm_cb.devcb.p_txpwer_cmpl_cb = p_cb;

    if (!btsnd_hcic_read_inq_tx_power ()) {
        btm_cb.devcb.p_txpwer_cmpl_cb = NULL;
        btu_stop_timer (&btm_cb.devcb.txpwer_timer);
        return (BTM_NO_RESOURCES);
    } else {
        return (BTM_CMD_STARTED);
    }
}