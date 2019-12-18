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
struct TYPE_4__ {scalar_t__ tcpip_if; scalar_t__ ip_protocol; struct TYPE_4__* next; } ;
typedef  TYPE_1__ mdns_tx_packet_t ;
typedef  scalar_t__ mdns_ip_protocol_t ;
typedef  scalar_t__ mdns_if_t ;
struct TYPE_5__ {TYPE_1__* tx_queue_head; } ;

/* Variables and functions */
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static mdns_tx_packet_t * _mdns_get_next_pcb_packet(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    mdns_tx_packet_t * q = _mdns_server->tx_queue_head;
    while (q) {
        if (q->tcpip_if == tcpip_if && q->ip_protocol == ip_protocol) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}