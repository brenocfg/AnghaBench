#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mdns_if_t ;
struct TYPE_6__ {TYPE_2__* interfaces; } ;
struct TYPE_5__ {TYPE_1__* pcbs; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 size_t MDNS_IF_MAX ; 
 size_t MDNS_IP_PROTOCOL_V4 ; 
 size_t MDNS_IP_PROTOCOL_V6 ; 
 scalar_t__ PCB_DUP ; 
 size_t _mdns_get_other_if (size_t) ; 
 TYPE_3__* _mdns_server ; 

__attribute__((used)) static bool _mdns_if_is_dup(mdns_if_t tcpip_if)
{
    mdns_if_t other_if = _mdns_get_other_if (tcpip_if);
    if (other_if == MDNS_IF_MAX) {
        return false;
    }
    if (_mdns_server->interfaces[tcpip_if].pcbs[MDNS_IP_PROTOCOL_V4].state == PCB_DUP
        || _mdns_server->interfaces[tcpip_if].pcbs[MDNS_IP_PROTOCOL_V6].state == PCB_DUP
        || _mdns_server->interfaces[other_if].pcbs[MDNS_IP_PROTOCOL_V4].state == PCB_DUP
        || _mdns_server->interfaces[other_if].pcbs[MDNS_IP_PROTOCOL_V6].state == PCB_DUP
    ) {
        return true;
    }
    return false;
}