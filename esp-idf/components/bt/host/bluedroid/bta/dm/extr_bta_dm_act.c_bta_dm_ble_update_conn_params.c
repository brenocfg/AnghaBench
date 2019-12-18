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
struct TYPE_4__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  max_int; int /*<<< orphan*/  min_int; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_5__ {TYPE_1__ ble_update_conn_params; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CA_UpdateBleConnParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_ble_update_conn_params (tBTA_DM_MSG *p_data)
{
    if (!L2CA_UpdateBleConnParams(p_data->ble_update_conn_params.bd_addr,
                                  p_data->ble_update_conn_params.min_int,
                                  p_data->ble_update_conn_params.max_int,
                                  p_data->ble_update_conn_params.latency,
                                  p_data->ble_update_conn_params.timeout)) {
        APPL_TRACE_ERROR("Update connection parameters failed!");
    }
}