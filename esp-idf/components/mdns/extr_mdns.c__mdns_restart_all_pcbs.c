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
struct TYPE_5__ {TYPE_1__* services; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mdns_clear_tx_queue_head () ; 
 int /*<<< orphan*/  _mdns_probe_all_pcbs (TYPE_1__**,size_t,int,int) ; 
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static void _mdns_restart_all_pcbs(void)
{
    _mdns_clear_tx_queue_head();
    size_t srv_count = 0;
    mdns_srv_item_t * a = _mdns_server->services;
    while (a) {
        srv_count++;
        a = a->next;
    }
    mdns_srv_item_t * services[srv_count];
    size_t l = 0;
    a = _mdns_server->services;
    while (a) {
        services[l++] = a;
        a = a->next;
    }

    _mdns_probe_all_pcbs(services, srv_count, true, true);
}