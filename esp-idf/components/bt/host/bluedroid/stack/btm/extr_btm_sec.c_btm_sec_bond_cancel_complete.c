#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  security_required; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_bond_cancel_cmpl_callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int pairing_flags; scalar_t__ pairing_state; TYPE_1__ api; int /*<<< orphan*/  pairing_bda; } ;

/* Variables and functions */
 int BTM_PAIR_FLAGS_DISC_WHEN_DONE ; 
 int BTM_PAIR_FLAGS_WE_CANCEL_DD ; 
 int BTM_PAIR_FLAGS_WE_STARTED_DD ; 
 scalar_t__ BTM_PAIR_STATE_GET_REM_NAME ; 
 int /*<<< orphan*/  BTM_PAIR_STATE_IDLE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_LOCAL_PIN ; 
 int /*<<< orphan*/  BTM_SEC_NONE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 TYPE_4__ btm_cb ; 
 TYPE_2__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btm_sec_bond_cancel_complete (void)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((btm_cb.pairing_flags & BTM_PAIR_FLAGS_DISC_WHEN_DONE) ||
            (BTM_PAIR_STATE_WAIT_LOCAL_PIN == btm_cb.pairing_state &&
             BTM_PAIR_FLAGS_WE_STARTED_DD & btm_cb.pairing_flags) ||
            (btm_cb.pairing_state == BTM_PAIR_STATE_GET_REM_NAME &&
             BTM_PAIR_FLAGS_WE_CANCEL_DD & btm_cb.pairing_flags)) {
        /* for dedicated bonding in legacy mode, authentication happens at "link level"
         * btm_sec_connected is called with failed status.
         * In theory, the code that handles is_pairing_device/TRUE should clean out security related code.
         * However, this function may clean out the security related flags and btm_sec_connected would not know
         * this function also needs to do proper clean up.
         */
        if ((p_dev_rec = btm_find_dev (btm_cb.pairing_bda)) != NULL) {
            p_dev_rec->security_required = BTM_SEC_NONE;
        }
        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

        /* Notify application that the cancel succeeded */
        if (btm_cb.api.p_bond_cancel_cmpl_callback) {
            btm_cb.api.p_bond_cancel_cmpl_callback(BTM_SUCCESS);
        }
    }
}