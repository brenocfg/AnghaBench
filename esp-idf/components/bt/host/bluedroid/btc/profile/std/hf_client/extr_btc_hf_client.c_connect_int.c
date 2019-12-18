#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
struct TYPE_9__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_3__ bt_bdaddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  address; } ;
struct TYPE_8__ {TYPE_1__ connected_bda; int /*<<< orphan*/  handle; int /*<<< orphan*/  state; } ;
struct TYPE_10__ {TYPE_2__ btc_hf_client_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HfClientOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTC_HF_CLIENT_SECURITY ; 
 int /*<<< orphan*/  BT_STATUS_BUSY ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CONNECTION_STATE_CONNECTING ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ hf_client_local_param ; 
 scalar_t__ is_connected (TYPE_3__*) ; 

__attribute__((used)) static bt_status_t connect_int( bt_bdaddr_t *bd_addr, uint16_t uuid )
{
    if (is_connected(bd_addr)) {
        return BT_STATUS_BUSY;
    }

    hf_client_local_param.btc_hf_client_cb.state = ESP_HF_CLIENT_CONNECTION_STATE_CONNECTING;
    bdcpy(hf_client_local_param.btc_hf_client_cb.connected_bda.address, bd_addr->address);

    BTA_HfClientOpen(hf_client_local_param.btc_hf_client_cb.handle, hf_client_local_param.btc_hf_client_cb.connected_bda.address,
               BTC_HF_CLIENT_SECURITY);

    return BT_STATUS_SUCCESS;
}