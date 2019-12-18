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
struct TYPE_4__ {scalar_t__ state; scalar_t__ pcb; } ;

/* Variables and functions */
 size_t MDNS_IF_MAX ; 
 scalar_t__ PCB_DUP ; 
 void* PCB_OFF ; 
 int /*<<< orphan*/  _mdns_clear_pcb_tx_queue_head (size_t,size_t) ; 
 int /*<<< orphan*/  _mdns_enable_pcb (size_t,size_t) ; 
 size_t _mdns_get_other_if (size_t) ; 
 int /*<<< orphan*/  _mdns_pcb_deinit (size_t,size_t) ; 
 TYPE_3__* _mdns_server ; 

void _mdns_disable_pcb(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    if (_mdns_server->interfaces[tcpip_if].pcbs[ip_protocol].pcb) {
        _mdns_clear_pcb_tx_queue_head(tcpip_if, ip_protocol);
        _mdns_pcb_deinit(tcpip_if, ip_protocol);
        mdns_if_t other_if = _mdns_get_other_if (tcpip_if);
        if (other_if != MDNS_IF_MAX && _mdns_server->interfaces[other_if].pcbs[ip_protocol].state == PCB_DUP) {
            _mdns_server->interfaces[other_if].pcbs[ip_protocol].state = PCB_OFF;
            _mdns_enable_pcb(other_if, ip_protocol);
        }
    }
    _mdns_server->interfaces[tcpip_if].pcbs[ip_protocol].state = PCB_OFF;
}