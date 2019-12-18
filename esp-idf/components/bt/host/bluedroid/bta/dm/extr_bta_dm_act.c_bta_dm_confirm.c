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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_4__ {scalar_t__ accept; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_5__ {TYPE_1__ confirm; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ConfirmReqReply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 scalar_t__ TRUE ; 

void bta_dm_confirm(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS res = BTM_NOT_AUTHORIZED;

    if (p_data->confirm.accept == TRUE) {
        res = BTM_SUCCESS;
    }
    BTM_ConfirmReqReply(res, p_data->confirm.bd_addr);
}