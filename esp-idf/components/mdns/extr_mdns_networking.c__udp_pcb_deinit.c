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
struct TYPE_5__ {int probe_ip; int probe_running; scalar_t__ failed_probes; scalar_t__ probe_services_len; int /*<<< orphan*/ * probe_services; int /*<<< orphan*/ * pcb; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ mdns_pcb_t ;
typedef  size_t mdns_ip_protocol_t ;
typedef  size_t mdns_if_t ;
struct TYPE_6__ {TYPE_1__* interfaces; } ;
struct TYPE_4__ {TYPE_2__* pcbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCB_OFF ; 
 TYPE_3__* _mdns_server ; 
 int /*<<< orphan*/  _udp_join_group (size_t,size_t,int) ; 
 int /*<<< orphan*/  _udp_pcb_is_in_use () ; 
 int /*<<< orphan*/  _udp_pcb_main_deinit () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _udp_pcb_deinit(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    if (!_mdns_server) {
        return;
    }
    mdns_pcb_t * _pcb = &_mdns_server->interfaces[tcpip_if].pcbs[ip_protocol];
    if (_pcb->pcb) {
        free(_pcb->probe_services);
        _pcb->state = PCB_OFF;
        _pcb->pcb = NULL;
        _pcb->probe_ip = false;
        _pcb->probe_services = NULL;
        _pcb->probe_services_len = 0;
        _pcb->probe_running = false;
        _pcb->failed_probes = 0;
        _udp_join_group(tcpip_if, ip_protocol, false);
        if(!_udp_pcb_is_in_use()) {
            _udp_pcb_main_deinit();
        }
    }
}