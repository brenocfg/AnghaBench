#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  portTickType ;
struct TYPE_10__ {int queued; int send_at; struct TYPE_10__* next; } ;
typedef  TYPE_3__ mdns_tx_packet_t ;
struct TYPE_8__ {TYPE_3__* packet; } ;
struct TYPE_9__ {TYPE_1__ tx_handle; } ;
struct TYPE_11__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ mdns_action_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  action_queue; TYPE_3__* tx_queue_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_TX_HANDLE ; 
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 int /*<<< orphan*/  MDNS_SERVICE_LOCK () ; 
 int /*<<< orphan*/  MDNS_SERVICE_UNLOCK () ; 
 TYPE_7__* _mdns_server ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pdPASS ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int xTaskGetTickCount () ; 

__attribute__((used)) static void _mdns_scheduler_run(void)
{
    MDNS_SERVICE_LOCK();
    mdns_tx_packet_t * p = _mdns_server->tx_queue_head;
    mdns_action_t * action = NULL;

    // find first unqueued packet
    while (p && p->queued) {
        p = p->next;
    }
    if (!p) {
        MDNS_SERVICE_UNLOCK();
        return;
    }
    if ((int32_t)(p->send_at - (xTaskGetTickCount() * portTICK_PERIOD_MS)) < 0) {
        action = (mdns_action_t *)malloc(sizeof(mdns_action_t));
        if (action) {
            action->type = ACTION_TX_HANDLE;
            action->data.tx_handle.packet = p;
            p->queued = true;
            if (xQueueSend(_mdns_server->action_queue, &action, (portTickType)0) != pdPASS) {
                free(action);
                p->queued = false;
            }
        } else {
            HOOK_MALLOC_FAILED;
            // continue
        }
    }
    MDNS_SERVICE_UNLOCK();
}