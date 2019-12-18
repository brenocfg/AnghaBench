#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  portTickType ;
typedef  int /*<<< orphan*/  mdns_rx_packet_t ;
struct TYPE_7__ {int /*<<< orphan*/ * packet; } ;
struct TYPE_8__ {TYPE_1__ rx_handle; } ;
struct TYPE_9__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mdns_action_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_10__ {int /*<<< orphan*/  action_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_RX_HANDLE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 TYPE_6__* _mdns_server ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pdPASS ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ ) ; 

esp_err_t _mdns_send_rx_action(mdns_rx_packet_t * packet)
{
    mdns_action_t * action = NULL;

    action = (mdns_action_t *)malloc(sizeof(mdns_action_t));
    if (!action) {
        HOOK_MALLOC_FAILED;
        return ESP_ERR_NO_MEM;
    }

    action->type = ACTION_RX_HANDLE;
    action->data.rx_handle.packet = packet;
    if (xQueueSend(_mdns_server->action_queue, &action, (portTickType)0) != pdPASS) {
        free(action);
        return ESP_ERR_NO_MEM;
    }
    return ESP_OK;
}