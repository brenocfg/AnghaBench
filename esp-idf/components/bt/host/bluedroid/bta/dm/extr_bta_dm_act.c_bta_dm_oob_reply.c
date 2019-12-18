#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  len; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_5__ {TYPE_1__ oob_reply; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleOobDataReply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 

void bta_dm_oob_reply(tBTA_DM_MSG *p_data)
{
#if (BLE_INCLUDED)
    BTM_BleOobDataReply(p_data->oob_reply.bd_addr, BTM_SUCCESS, p_data->oob_reply.len, p_data->oob_reply.value);
#endif
}