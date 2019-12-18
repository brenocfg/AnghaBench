#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sec_bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_auth_complete_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ param; } ;
struct TYPE_9__ {TYPE_2__ api; TYPE_3__* p_collided_dev_rec; TYPE_1__ sec_collision_tle; } ;
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_PAIR_STATE_IDLE ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  HCI_ERR_MEMORY_FULL ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (int /*<<< orphan*/ ) ; 
 scalar_t__ btm_sec_dd_create_conn (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btm_sec_connect_after_reject_timeout (TIMER_LIST_ENT *p_tle)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_cb.p_collided_dev_rec;
    UNUSED(p_tle);

    BTM_TRACE_EVENT ("btm_sec_connect_after_reject_timeout()\n");
    btm_cb.sec_collision_tle.param = 0;
    btm_cb.p_collided_dev_rec = 0;

    if (btm_sec_dd_create_conn(p_dev_rec) != BTM_CMD_STARTED) {
        BTM_TRACE_WARNING ("Security Manager: btm_sec_connect_after_reject_timeout: failed to start connection\n");

        btm_sec_change_pairing_state (BTM_PAIR_STATE_IDLE);

        if (btm_cb.api.p_auth_complete_callback) {
            (*btm_cb.api.p_auth_complete_callback) (p_dev_rec->bd_addr,  p_dev_rec->dev_class,
                                                    p_dev_rec->sec_bd_name, HCI_ERR_MEMORY_FULL);
        }
    }
}