#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ opcode; int /*<<< orphan*/  param_buf; } ;
typedef  TYPE_2__ tBTM_RAND_ENC ;
struct TYPE_5__ {int /*<<< orphan*/ * ble_encryption_key_value; } ;
struct TYPE_7__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BT_OCTET8_LEN ; 
 scalar_t__ HCI_BLE_RAND ; 
 scalar_t__ btm_ble_process_er2 ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_ble_rand (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btm_ble_process_er(tBTM_RAND_ENC *p)
{
    BTM_TRACE_DEBUG ("btm_ble_process_er");

    if (p && p->opcode == HCI_BLE_RAND) {
        memcpy(&btm_cb.devcb.ble_encryption_key_value[0], p->param_buf, BT_OCTET8_LEN);

        if (!btsnd_hcic_ble_rand((void *)btm_ble_process_er2)) {
            memset(&btm_cb.devcb.ble_encryption_key_value, 0, sizeof(BT_OCTET16));
            BTM_TRACE_ERROR("Generating ER2 failed.");
        }
    } else {
        BTM_TRACE_ERROR("Generating ER1 exception.");
    }
}