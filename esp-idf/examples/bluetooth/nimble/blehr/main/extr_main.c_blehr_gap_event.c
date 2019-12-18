#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* conn_handle; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {char* cur_notify; int /*<<< orphan*/  attr_handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  reason; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn_handle; int /*<<< orphan*/  status; } ;
struct ble_gap_event {int type; TYPE_4__ mtu; TYPE_3__ subscribe; TYPE_2__ disconnect; TYPE_1__ connect; } ;

/* Variables and functions */
#define  BLE_GAP_EVENT_ADV_COMPLETE 132 
#define  BLE_GAP_EVENT_CONNECT 131 
#define  BLE_GAP_EVENT_DISCONNECT 130 
#define  BLE_GAP_EVENT_MTU 129 
#define  BLE_GAP_EVENT_SUBSCRIBE 128 
 int /*<<< orphan*/  ESP_LOGI (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MODLOG_DFLT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  blehr_advertise () ; 
 int /*<<< orphan*/  blehr_tx_hrate_reset () ; 
 int /*<<< orphan*/  blehr_tx_hrate_stop () ; 
 int /*<<< orphan*/  conn_handle ; 
 int /*<<< orphan*/  hrs_hrm_handle ; 
 char* notify_state ; 

__attribute__((used)) static int
blehr_gap_event(struct ble_gap_event *event, void *arg)
{
    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
        /* A new connection was established or a connection attempt failed */
        MODLOG_DFLT(INFO, "connection %s; status=%d\n",
                    event->connect.status == 0 ? "established" : "failed",
                    event->connect.status);

        if (event->connect.status != 0) {
            /* Connection failed; resume advertising */
            blehr_advertise();
        }
        conn_handle = event->connect.conn_handle;
        break;

    case BLE_GAP_EVENT_DISCONNECT:
        MODLOG_DFLT(INFO, "disconnect; reason=%d\n", event->disconnect.reason);

        /* Connection terminated; resume advertising */
        blehr_advertise();
        break;

    case BLE_GAP_EVENT_ADV_COMPLETE:
        MODLOG_DFLT(INFO, "adv complete\n");
        blehr_advertise();
        break;

    case BLE_GAP_EVENT_SUBSCRIBE:
        MODLOG_DFLT(INFO, "subscribe event; cur_notify=%d\n value handle; "
                    "val_handle=%d\n",
                    event->subscribe.cur_notify, hrs_hrm_handle);
        if (event->subscribe.attr_handle == hrs_hrm_handle) {
            notify_state = event->subscribe.cur_notify;
            blehr_tx_hrate_reset();
        } else if (event->subscribe.attr_handle != hrs_hrm_handle) {
            notify_state = event->subscribe.cur_notify;
            blehr_tx_hrate_stop();
        }
        ESP_LOGI("BLE_GAP_SUBSCRIBE_EVENT", "conn_handle from subscribe=%d", conn_handle);
        break;

    case BLE_GAP_EVENT_MTU:
        MODLOG_DFLT(INFO, "mtu update event; conn_handle=%d mtu=%d\n",
                    event->mtu.conn_handle,
                    event->mtu.value);
        break;

    }

    return 0;
}