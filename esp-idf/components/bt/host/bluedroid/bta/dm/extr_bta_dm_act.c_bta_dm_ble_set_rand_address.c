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
struct TYPE_4__ {scalar_t__ addr_type; int /*<<< orphan*/  (* p_set_rand_addr_cback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  address; } ;
struct TYPE_5__ {TYPE_1__ set_addr; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,scalar_t__) ; 
 scalar_t__ BLE_ADDR_RANDOM ; 
 int /*<<< orphan*/  BTM_BleSetRandAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_SET_STATIC_RAND_ADDR_FAIL ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void bta_dm_ble_set_rand_address(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS status = BTM_SET_STATIC_RAND_ADDR_FAIL;
    if (p_data->set_addr.addr_type != BLE_ADDR_RANDOM) {
        APPL_TRACE_ERROR("Invalid random adress type = %d\n", p_data->set_addr.addr_type);
        if(p_data->set_addr.p_set_rand_addr_cback) {
            (*p_data->set_addr.p_set_rand_addr_cback)(status);
        }
        return;
    }
    //send the setting random address to BTM layer
    status = BTM_BleSetRandAddress(p_data->set_addr.address);
    if(p_data->set_addr.p_set_rand_addr_cback) {
        (*p_data->set_addr.p_set_rand_addr_cback)(status);
    }

}