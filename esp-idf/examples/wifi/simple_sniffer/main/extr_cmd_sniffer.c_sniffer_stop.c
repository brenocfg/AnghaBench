#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_running; int interf; int /*<<< orphan*/  pcap; int /*<<< orphan*/ * work_queue; int /*<<< orphan*/ * sem_task_over; } ;
typedef  TYPE_1__ sniffer_runtime_t ;
struct TYPE_6__ {int /*<<< orphan*/  payload; } ;
typedef  TYPE_2__ sniffer_packet_info_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  UBaseType_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SNIFFER_CHECK (int,char*,int /*<<< orphan*/ ) ; 
#define  SNIFFER_INTF_WLAN 128 
 int /*<<< orphan*/  SNIFFER_PROCESS_PACKET_TIMEOUT_MS ; 
 int /*<<< orphan*/  SNIFFER_TAG ; 
 int /*<<< orphan*/  err ; 
 scalar_t__ esp_wifi_set_promiscuous (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ pcap_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  uxQueueMessagesWaiting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xQueueReceive (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t sniffer_stop(sniffer_runtime_t *sniffer)
{
    SNIFFER_CHECK(sniffer->is_running, "sniffer is already stopped", err);

    switch (sniffer->interf) {
    case SNIFFER_INTF_WLAN:
        /* Disable wifi promiscuous mode */
        SNIFFER_CHECK(esp_wifi_set_promiscuous(false) == ESP_OK, "stop wifi promiscuous failed", err);
        break;
    default:
        SNIFFER_CHECK(false, "unsupported interface", err);
        break;
    }
    ESP_LOGI(SNIFFER_TAG, "stop WiFi promiscuous ok");

    /* stop sniffer local task */
    sniffer->is_running = false;
    /* wait for task over */
    xSemaphoreTake(sniffer->sem_task_over, portMAX_DELAY);
    vSemaphoreDelete(sniffer->sem_task_over);
    sniffer->sem_task_over = NULL;
    /* make sure to free all resources in the left items */
    UBaseType_t left_items = uxQueueMessagesWaiting(sniffer->work_queue);
    sniffer_packet_info_t packet_info;
    while (left_items--) {
        xQueueReceive(sniffer->work_queue, &packet_info, pdMS_TO_TICKS(SNIFFER_PROCESS_PACKET_TIMEOUT_MS));
        free(packet_info.payload);
    }
    vQueueDelete(sniffer->work_queue);
    sniffer->work_queue = NULL;
    /* stop pcap session */
    SNIFFER_CHECK(pcap_deinit(sniffer->pcap) == ESP_OK, "stop pcap session failed", err);
    return ESP_OK;
err:
    return ESP_FAIL;
}