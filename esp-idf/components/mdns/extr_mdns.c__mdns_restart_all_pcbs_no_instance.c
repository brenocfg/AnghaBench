#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__* service; } ;
typedef  TYPE_2__ mdns_srv_item_t ;
struct TYPE_7__ {TYPE_2__* services; } ;
struct TYPE_5__ {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mdns_probe_all_pcbs (TYPE_2__**,size_t,int,int) ; 
 TYPE_3__* _mdns_server ; 

__attribute__((used)) static void _mdns_restart_all_pcbs_no_instance(void)
{
    size_t srv_count = 0;
    mdns_srv_item_t * a = _mdns_server->services;
    while (a) {
        if (!a->service->instance) {
            srv_count++;
        }
        a = a->next;
    }
    if (!srv_count) {
        return;
    }
    mdns_srv_item_t * services[srv_count];
    size_t i = 0;
    a = _mdns_server->services;
    while (a) {
        if (!a->service->instance) {
            services[i++] = a;
        }
        a = a->next;
    }
    _mdns_probe_all_pcbs(services, srv_count, false, true);
}