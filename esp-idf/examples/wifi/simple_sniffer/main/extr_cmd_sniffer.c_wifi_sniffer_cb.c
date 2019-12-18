#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wifi_promiscuous_pkt_type_t ;
struct TYPE_6__ {unsigned int timestamp; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  sig_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  payload; TYPE_1__ rx_ctrl; } ;
typedef  TYPE_2__ wifi_promiscuous_pkt_t ;
struct TYPE_8__ {unsigned int seconds; unsigned int microseconds; void* payload; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ sniffer_packet_info_t ;
struct TYPE_9__ {scalar_t__ work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SNIFFER_PAYLOAD_FCS_LEN ; 
 int /*<<< orphan*/  SNIFFER_PROCESS_PACKET_TIMEOUT_MS ; 
 int /*<<< orphan*/  SNIFFER_TAG ; 
 scalar_t__ WIFI_PKT_MISC ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 scalar_t__ pdTRUE ; 
 TYPE_5__ snf_rt ; 
 scalar_t__ xQueueSend (scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wifi_sniffer_cb(void *recv_buf, wifi_promiscuous_pkt_type_t type)
{
    sniffer_packet_info_t packet_info;
    wifi_promiscuous_pkt_t *sniffer = (wifi_promiscuous_pkt_t *)recv_buf;
    /* prepare packet_info */
    packet_info.seconds = sniffer->rx_ctrl.timestamp / 1000000U;
    packet_info.microseconds = sniffer->rx_ctrl.timestamp % 1000000U;
    packet_info.length = sniffer->rx_ctrl.sig_len;
    /* For now, the sniffer only dumps the length of the MISC type frame */
    if (type != WIFI_PKT_MISC && !sniffer->rx_ctrl.rx_state) {
        packet_info.length -= SNIFFER_PAYLOAD_FCS_LEN;
        void *backup = malloc(packet_info.length);
        if (backup) {
            memcpy(backup, sniffer->payload, packet_info.length);
            packet_info.payload = backup;
            if (snf_rt.work_queue) {
                /* send packet_info */
                if (xQueueSend(snf_rt.work_queue, &packet_info, pdMS_TO_TICKS(SNIFFER_PROCESS_PACKET_TIMEOUT_MS)) != pdTRUE) {
                    ESP_LOGE(SNIFFER_TAG, "sniffer work queue full");
                }
            }
        } else {
            ESP_LOGE(SNIFFER_TAG, "No enough memory for promiscuous packet");
        }
    }
}