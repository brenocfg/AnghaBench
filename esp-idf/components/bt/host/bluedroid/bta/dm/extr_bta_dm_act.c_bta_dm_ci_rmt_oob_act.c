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
struct TYPE_4__ {scalar_t__ accept; int /*<<< orphan*/  r; int /*<<< orphan*/  c; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_5__ {TYPE_1__ ci_rmt_oob; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  BTM_RemoteOobDataReply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 scalar_t__ TRUE ; 

void bta_dm_ci_rmt_oob_act(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS res = BTM_NOT_AUTHORIZED;

    if (p_data->ci_rmt_oob.accept == TRUE) {
        res = BTM_SUCCESS;
    }
    BTM_RemoteOobDataReply(res, p_data->ci_rmt_oob.bd_addr,
                           p_data->ci_rmt_oob.c, p_data->ci_rmt_oob.r );
}