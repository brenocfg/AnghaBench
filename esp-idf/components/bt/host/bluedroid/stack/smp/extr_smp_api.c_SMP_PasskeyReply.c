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
struct TYPE_4__ {scalar_t__ cb_evt; scalar_t__ state; scalar_t__ selected_association_model; int /*<<< orphan*/  tk; int /*<<< orphan*/  pairing_bda; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_MAX_PASSKEY_VAL ; 
 int /*<<< orphan*/  SMP_AUTH_CMPL_EVT ; 
 scalar_t__ SMP_MODEL_SEC_CONN_PASSKEY_ENT ; 
 scalar_t__ SMP_PASSKEY_ENTRY_FAIL ; 
 scalar_t__ SMP_PASSKEY_REQ_EVT ; 
 int /*<<< orphan*/  SMP_SC_KEY_READY_EVT ; 
 scalar_t__ SMP_SUCCESS ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SMP_TRACE_WARNING (char*,scalar_t__) ; 
 int /*<<< orphan*/ * btm_find_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ smp_cb ; 
 int /*<<< orphan*/  smp_convert_string_to_tk (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 

void SMP_PasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey)
{
    tSMP_CB *p_cb = & smp_cb;
    UINT8   failure = SMP_PASSKEY_ENTRY_FAIL;

    SMP_TRACE_EVENT ("SMP_PasskeyReply: Key: %d  Result:%d",
                     passkey, res);

    /* If timeout already expired or has been canceled, ignore the reply */
    if (p_cb->cb_evt != SMP_PASSKEY_REQ_EVT) {
        SMP_TRACE_WARNING ("SMP_PasskeyReply() - Wrong State: %d", p_cb->state);
        return;
    }

    if (memcmp (bd_addr, p_cb->pairing_bda, BD_ADDR_LEN) != 0) {
        SMP_TRACE_ERROR ("SMP_PasskeyReply() - Wrong BD Addr");
        return;
    }

    if (btm_find_dev (bd_addr) == NULL) {
        SMP_TRACE_ERROR ("SMP_PasskeyReply() - no dev CB");
        return;
    }

    if (passkey > BTM_MAX_PASSKEY_VAL || res != SMP_SUCCESS) {
        SMP_TRACE_WARNING ("SMP_PasskeyReply() - Wrong key len: %d or passkey entry fail", passkey);
        /* send pairing failure */
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &failure);

    } else if (p_cb->selected_association_model == SMP_MODEL_SEC_CONN_PASSKEY_ENT) {
        smp_sm_event(&smp_cb, SMP_SC_KEY_READY_EVT, &passkey);
    } else {
        smp_convert_string_to_tk(p_cb->tk, passkey);
    }

    return;
}