#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p_data; int /*<<< orphan*/  key_type; } ;
typedef  TYPE_1__ tSMP_KEY ;
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
typedef  int /*<<< orphan*/  tSMP_EVT_DATA ;
struct TYPE_6__ {scalar_t__ selected_association_model; int /*<<< orphan*/  pairing_bda; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * tk; int /*<<< orphan*/  static_passkey; } ;
typedef  TYPE_2__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_KEY_READY_EVT ; 
 int /*<<< orphan*/  SMP_KEY_TYPE_TK ; 
 scalar_t__ SMP_MODEL_SEC_CONN_PASSKEY_DISP ; 
 int /*<<< orphan*/  SMP_PASSKEY_NOTIF_EVT ; 
 int /*<<< orphan*/  UINT32_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ smp_cb ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void smp_use_static_passkey(void)
{
    tSMP_CB *p_cb = &smp_cb;
    UINT8   *tt = p_cb->tk;
    tSMP_KEY    key;
    UINT32  passkey = p_cb->static_passkey;
    /* save the TK */
    memset(p_cb->tk, 0, BT_OCTET16_LEN);
    UINT32_TO_STREAM(tt, passkey);

    key.key_type = SMP_KEY_TYPE_TK;
    key.p_data  = p_cb->tk;

    if (p_cb->p_callback) {
        (*p_cb->p_callback)(SMP_PASSKEY_NOTIF_EVT, p_cb->pairing_bda, (tSMP_EVT_DATA *)&passkey);
    }

    if (p_cb->selected_association_model == SMP_MODEL_SEC_CONN_PASSKEY_DISP) {
        smp_sm_event(&smp_cb, SMP_KEY_READY_EVT, &passkey);
    } else {
        smp_sm_event(p_cb, SMP_KEY_READY_EVT, (tSMP_INT_DATA *)&key);
    }
}