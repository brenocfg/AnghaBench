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
struct TYPE_4__ {int /*<<< orphan*/  sem_task_over; int /*<<< orphan*/  pcap; int /*<<< orphan*/  work_queue; scalar_t__ is_running; } ;
typedef  TYPE_1__ sniffer_runtime_t ;
struct TYPE_5__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  microseconds; int /*<<< orphan*/  seconds; int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ sniffer_packet_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SNIFFER_PROCESS_PACKET_TIMEOUT_MS ; 
 int /*<<< orphan*/  SNIFFER_TAG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ pcap_capture_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xQueueReceive (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sniffer_task(void *parameters)
{
    sniffer_packet_info_t packet_info;
    sniffer_runtime_t *sniffer = (sniffer_runtime_t *)parameters;

    while (sniffer->is_running) {
        /* receive paclet info from queue */
        if (xQueueReceive(sniffer->work_queue, &packet_info, pdMS_TO_TICKS(SNIFFER_PROCESS_PACKET_TIMEOUT_MS)) != pdTRUE) {
            continue;
        }
        if (pcap_capture_packet(sniffer->pcap, packet_info.payload, packet_info.length,
                                packet_info.seconds, packet_info.microseconds) != ESP_OK) {
            ESP_LOGW(SNIFFER_TAG, "save captured packet failed");
        }
        free(packet_info.payload);
    }
    /* notify that sniffer task is over */
    xSemaphoreGive(sniffer->sem_task_over);
    vTaskDelete(NULL);
}