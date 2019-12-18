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
struct TYPE_6__ {int sec_flags; int /*<<< orphan*/  link_key; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_7__ {scalar_t__ pairing_state; scalar_t__ collision_start_time; TYPE_1__* p_collided_dev_rec; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_PIN_REQ ; 
 int BTM_SEC_LINK_KEY_KNOWN ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,scalar_t__,scalar_t__,...) ; 
 TYPE_4__ btm_cb ; 
 TYPE_2__* btm_find_or_alloc_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_link_key_neg_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_link_key_req_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_pin_code_request (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btm_sec_link_key_request (UINT8 *p_bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_or_alloc_dev (p_bda);

    BTM_TRACE_EVENT ("btm_sec_link_key_request()  BDA: %02x:%02x:%02x:%02x:%02x:%02x\n",
                     p_bda[0], p_bda[1], p_bda[2], p_bda[3], p_bda[4], p_bda[5]);

    if ( (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_PIN_REQ) &&
            (btm_cb.collision_start_time != 0) &&
            (memcmp (btm_cb.p_collided_dev_rec->bd_addr, p_bda, BD_ADDR_LEN) == 0) ) {
        BTM_TRACE_EVENT ("btm_sec_link_key_request() rejecting link key req "
                         "State: %d START_TIMEOUT : %d\n",
                         btm_cb.pairing_state, btm_cb.collision_start_time);
        btsnd_hcic_link_key_neg_reply (p_bda);
        return;
    }
    if (p_dev_rec->sec_flags & BTM_SEC_LINK_KEY_KNOWN) {
        btsnd_hcic_link_key_req_reply (p_bda, p_dev_rec->link_key);
        return;
    }

    /* Notify L2CAP to increase timeout */
    l2c_pin_code_request (p_bda);

    /* The link key is not in the database and it is not known to the manager */
    btsnd_hcic_link_key_neg_reply (p_bda);
}