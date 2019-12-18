#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_4__ {scalar_t__ br_state; scalar_t__ cb_evt; scalar_t__ state; int /*<<< orphan*/  pairing_bda; scalar_t__ smp_over_br; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  SMP_API_SEC_GRANT_EVT ; 
 int /*<<< orphan*/  SMP_BR_API_SEC_GRANT_EVT ; 
 scalar_t__ SMP_BR_STATE_WAIT_APP_RSP ; 
 scalar_t__ SMP_SEC_REQUEST_EVT ; 
 scalar_t__ SMP_STATE_WAIT_APP_RSP ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_br_state_machine_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ smp_cb ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void SMP_SecurityGrant(BD_ADDR bd_addr, UINT8 res)
{
    SMP_TRACE_EVENT ("SMP_SecurityGrant ");

#if (CLASSIC_BT_INCLUDED == TRUE)
    if (smp_cb.smp_over_br) {
        if (smp_cb.br_state != SMP_BR_STATE_WAIT_APP_RSP ||
                smp_cb.cb_evt != SMP_SEC_REQUEST_EVT ||
                memcmp (smp_cb.pairing_bda, bd_addr, BD_ADDR_LEN)) {
            return;
        }

        /* clear the SMP_SEC_REQUEST_EVT event after get grant */
        /* avoid generating duplicate pair request */
        smp_cb.cb_evt = 0;
        smp_br_state_machine_event(&smp_cb, SMP_BR_API_SEC_GRANT_EVT, &res);
        return;
    }
#endif  ///CLASSIC_BT_INCLUDED == TRUE

    if (smp_cb.state != SMP_STATE_WAIT_APP_RSP ||
            smp_cb.cb_evt != SMP_SEC_REQUEST_EVT ||
            memcmp (smp_cb.pairing_bda, bd_addr, BD_ADDR_LEN)) {
        return;
    }
    /* clear the SMP_SEC_REQUEST_EVT event after get grant */
    /* avoid generate duplicate pair request */
    smp_cb.cb_evt = 0;
    smp_sm_event(&smp_cb, SMP_API_SEC_GRANT_EVT, &res);
}