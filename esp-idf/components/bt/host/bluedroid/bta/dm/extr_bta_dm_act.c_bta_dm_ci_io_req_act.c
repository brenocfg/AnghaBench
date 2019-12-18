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
typedef  int /*<<< orphan*/  tBTM_AUTH_REQ ;
struct TYPE_4__ {int /*<<< orphan*/  oob_data; int /*<<< orphan*/  io_cap; int /*<<< orphan*/  bd_addr; scalar_t__ auth_req; } ;
struct TYPE_5__ {TYPE_1__ ci_io_req; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_AUTH_AP_NO ; 
 int /*<<< orphan*/  BTM_AUTH_AP_YES ; 
 int /*<<< orphan*/  BTM_IoCapRsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_ci_io_req_act(tBTA_DM_MSG *p_data)
{
    tBTM_AUTH_REQ   auth_req = BTM_AUTH_AP_NO;
    if (p_data->ci_io_req.auth_req) {
        auth_req = BTM_AUTH_AP_YES;
    }
    BTM_IoCapRsp(p_data->ci_io_req.bd_addr, p_data->ci_io_req.io_cap,
                 p_data->ci_io_req.oob_data, auth_req);
}