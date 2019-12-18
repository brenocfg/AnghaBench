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
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ tcpip_if; scalar_t__ ip_protocol; struct TYPE_7__* next; TYPE_3__* answers; scalar_t__ distributed; } ;
typedef  TYPE_1__ mdns_tx_packet_t ;
struct TYPE_8__ {scalar_t__ service; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ mdns_srv_item_t ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ service; struct TYPE_9__* next; } ;
typedef  TYPE_3__ mdns_out_answer_t ;
typedef  scalar_t__ mdns_ip_protocol_t ;
typedef  scalar_t__ mdns_if_t ;
struct TYPE_10__ {TYPE_1__* tx_queue_head; } ;

/* Variables and functions */
 TYPE_5__* _mdns_server ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void _mdns_remove_scheduled_answer(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol, uint16_t type, mdns_srv_item_t * service)
{
    mdns_srv_item_t s = {NULL, NULL};
    if (!service) {
        service = &s;
    }
    mdns_tx_packet_t * q = _mdns_server->tx_queue_head;
    while (q) {
        if (q->tcpip_if == tcpip_if && q->ip_protocol == ip_protocol && q->distributed) {
            mdns_out_answer_t * a = q->answers;
            if (a->type == type && a->service == service->service) {
                q->answers = q->answers->next;
                free(a);
            } else {
                while (a->next) {
                    if (a->next->type == type && a->next->service == service->service) {
                        mdns_out_answer_t * b = a->next;
                        a->next = b->next;
                        free(b);
                        break;
                    }
                    a = a->next;
                }
            }
        }
        q = q->next;
    }
}