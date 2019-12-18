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
struct TYPE_6__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_addr; scalar_t__ accept; } ;
struct TYPE_7__ {TYPE_2__ ble_passkey_reply; TYPE_1__ confirm; } ;
typedef  TYPE_3__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleConfirmReply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 

void bta_dm_ble_confirm_reply (tBTA_DM_MSG *p_data)
{
    if (p_data->confirm.accept) {
        BTM_BleConfirmReply(p_data->confirm.bd_addr, BTM_SUCCESS);
    } else {
        BTM_BleConfirmReply(p_data->ble_passkey_reply.bd_addr, BTM_NOT_AUTHORIZED);
    }
}