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
struct TYPE_5__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  service; } ;

/* Variables and functions */
 TYPE_3__* _mdns_server ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static mdns_srv_item_t * _mdns_get_service_item(const char * service, const char * proto)
{
    mdns_srv_item_t * s = _mdns_server->services;
    while (s) {
        if (!strcasecmp(s->service->service, service) && !strcasecmp(s->service->proto, proto)) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}