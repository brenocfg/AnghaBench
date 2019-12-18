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
typedef  size_t mdns_ip_protocol_t ;
typedef  size_t mdns_if_t ;
struct TYPE_6__ {TYPE_2__* interfaces; } ;
struct TYPE_5__ {TYPE_1__* pcbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcb; } ;

/* Variables and functions */
 scalar_t__ _mdns_pcb_init (size_t,size_t) ; 
 int /*<<< orphan*/  _mdns_restart_pcb (size_t,size_t) ; 
 TYPE_3__* _mdns_server ; 

void _mdns_enable_pcb(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    if (!_mdns_server->interfaces[tcpip_if].pcbs[ip_protocol].pcb) {
        if (_mdns_pcb_init(tcpip_if, ip_protocol)) {
            return;
        }
    }
    _mdns_restart_pcb(tcpip_if, ip_protocol);
}