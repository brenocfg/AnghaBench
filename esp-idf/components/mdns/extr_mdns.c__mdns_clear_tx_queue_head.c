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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ mdns_tx_packet_t ;
struct TYPE_5__ {TYPE_1__* tx_queue_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mdns_free_tx_packet (TYPE_1__*) ; 
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static void _mdns_clear_tx_queue_head(void)
{
    mdns_tx_packet_t * q;
    while (_mdns_server->tx_queue_head) {
        q = _mdns_server->tx_queue_head;
        _mdns_server->tx_queue_head = _mdns_server->tx_queue_head->next;
        _mdns_free_tx_packet(q);
    }
}