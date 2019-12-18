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
struct TYPE_4__ {int /*<<< orphan*/  exceptional_list_cb; int /*<<< orphan*/  device_info; int /*<<< orphan*/  type; int /*<<< orphan*/  subcode; } ;
struct TYPE_5__ {TYPE_1__ ble_duplicate_exceptional_list; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_UpdateBleDuplicateExceptionalList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_ble_update_duplicate_exceptional_list(tBTA_DM_MSG *p_data)
{
    BTM_UpdateBleDuplicateExceptionalList(p_data->ble_duplicate_exceptional_list.subcode,
                                          p_data->ble_duplicate_exceptional_list.type,
                                          p_data->ble_duplicate_exceptional_list.device_info,
                                          p_data->ble_duplicate_exceptional_list.exceptional_list_cb);
}