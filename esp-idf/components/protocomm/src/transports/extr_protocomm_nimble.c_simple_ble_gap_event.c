#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  conn_handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  reason; } ;
struct TYPE_6__ {int /*<<< orphan*/  conn_handle; int /*<<< orphan*/  status; } ;
struct ble_gap_event {int type; TYPE_2__ mtu; TYPE_1__ disconnect; TYPE_3__ connect; } ;
struct ble_gap_conn_desc {int dummy; } ;

/* Variables and functions */
#define  BLE_GAP_EVENT_ADV_COMPLETE 131 
#define  BLE_GAP_EVENT_CONNECT 130 
#define  BLE_GAP_EVENT_DISCONNECT 129 
#define  BLE_GAP_EVENT_MTU 128 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int ble_gap_conn_find (int /*<<< orphan*/ ,struct ble_gap_conn_desc*) ; 
 int /*<<< orphan*/  simple_ble_advertise () ; 
 int /*<<< orphan*/  transport_simple_ble_connect (struct ble_gap_event*,void*) ; 
 int /*<<< orphan*/  transport_simple_ble_disconnect (struct ble_gap_event*,void*) ; 
 int /*<<< orphan*/  transport_simple_ble_set_mtu (struct ble_gap_event*,void*) ; 

__attribute__((used)) static int
simple_ble_gap_event(struct ble_gap_event *event, void *arg)
{
    struct ble_gap_conn_desc desc;
    int rc;

    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
        /* A new connection was established or a connection attempt failed. */
        if (event->connect.status == 0) {
            transport_simple_ble_connect(event, arg);
            rc = ble_gap_conn_find(event->connect.conn_handle, &desc);
            if (rc != 0) {
                ESP_LOGE(TAG, "No open connection with the specified handle");
                return rc;
            }
        } else {
            /* Connection failed; resume advertising. */
            simple_ble_advertise();
        }
        return 0;

    case BLE_GAP_EVENT_DISCONNECT:
        ESP_LOGD(TAG, "disconnect; reason=%d ", event->disconnect.reason);
        transport_simple_ble_disconnect(event, arg);

        /* Connection terminated; resume advertising. */
        simple_ble_advertise();
        return 0;

    case BLE_GAP_EVENT_ADV_COMPLETE:
        simple_ble_advertise();
        return 0;

    case BLE_GAP_EVENT_MTU:
        ESP_LOGI(TAG, "mtu update event; conn_handle=%d cid=%d mtu=%d\n",
                 event->mtu.conn_handle,
                 event->mtu.channel_id,
                 event->mtu.value);
        transport_simple_ble_set_mtu(event, arg);
        return 0;
    }
    return 0;
}