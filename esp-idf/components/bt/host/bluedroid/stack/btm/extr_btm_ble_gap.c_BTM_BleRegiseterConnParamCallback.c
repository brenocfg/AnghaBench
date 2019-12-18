#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_UPDATE_CONN_PARAM_CBACK ;
struct TYPE_2__ {int /*<<< orphan*/ * update_conn_param_cb; } ;

/* Variables and functions */
 TYPE_1__ conn_param_update_cb ; 

void BTM_BleRegiseterConnParamCallback(tBTM_UPDATE_CONN_PARAM_CBACK *update_conn_param_cb)
{
    conn_param_update_cb.update_conn_param_cb = update_conn_param_cb;
}