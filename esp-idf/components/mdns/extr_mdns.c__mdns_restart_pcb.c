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
typedef  TYPE_1__ mdns_srv_item_t ;
typedef  int /*<<< orphan*/  mdns_ip_protocol_t ;
typedef  int /*<<< orphan*/  mdns_if_t ;
struct TYPE_5__ {TYPE_1__* services; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mdns_init_pcb_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,size_t,int) ; 
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static void _mdns_restart_pcb(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    size_t srv_count = 0;
    mdns_srv_item_t * a = _mdns_server->services;
    while (a) {
        srv_count++;
        a = a->next;
    }
    mdns_srv_item_t * services[srv_count];
    size_t i = 0;
    a = _mdns_server->services;
    while (a) {
        services[i++] = a;
        a = a->next;
    }
    _mdns_init_pcb_probe(tcpip_if, ip_protocol, services, srv_count, true);
}