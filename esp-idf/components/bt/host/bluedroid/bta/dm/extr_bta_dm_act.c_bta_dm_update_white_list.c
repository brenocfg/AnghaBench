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
struct TYPE_4__ {int /*<<< orphan*/  add_wl_cb; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  add_remove; } ;
struct TYPE_5__ {TYPE_1__ white_list; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BleUpdateAdvWhitelist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_update_white_list(tBTA_DM_MSG *p_data)
{
#if (BLE_INCLUDED == TRUE)
    BTM_BleUpdateAdvWhitelist(p_data->white_list.add_remove, p_data->white_list.remote_addr, p_data->white_list.addr_type, p_data->white_list.add_wl_cb);
#endif  ///BLE_INCLUDED == TRUE
}