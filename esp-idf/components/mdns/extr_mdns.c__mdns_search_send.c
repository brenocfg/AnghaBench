#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ mdns_search_once_t ;
typedef  int /*<<< orphan*/  mdns_ip_protocol_t ;
typedef  int /*<<< orphan*/  mdns_if_t ;
struct TYPE_6__ {TYPE_1__* search_once; } ;

/* Variables and functions */
 scalar_t__ MDNS_IF_MAX ; 
 scalar_t__ MDNS_IP_PROTOCOL_MAX ; 
 int /*<<< orphan*/  _mdns_search_send_pcb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static void _mdns_search_send(mdns_search_once_t * search)
{
    mdns_search_once_t* queue = _mdns_server->search_once;
    bool found = false;
    // looking for this search in active searches
    while (queue) {
        if (queue == search) {
            found = true;
            break;
        }
        queue = queue->next;
    }

    if (!found) {
        // no longer active -> skip sending this search
        return;
    }

    uint8_t i, j;
    for (i=0; i<MDNS_IF_MAX; i++) {
        for (j=0; j<MDNS_IP_PROTOCOL_MAX; j++) {
            _mdns_search_send_pcb(search, (mdns_if_t)i, (mdns_ip_protocol_t)j);
        }
    }
}