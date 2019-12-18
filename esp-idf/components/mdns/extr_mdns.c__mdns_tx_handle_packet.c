#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {size_t tcpip_if; size_t ip_protocol; TYPE_4__* questions; } ;
typedef  TYPE_2__ mdns_tx_packet_t ;
struct TYPE_14__ {int state; int probe_running; int probe_ip; int /*<<< orphan*/ * probe_services; int /*<<< orphan*/  failed_probes; int /*<<< orphan*/  probe_services_len; } ;
typedef  TYPE_3__ mdns_pcb_t ;
typedef  void* mdns_pcb_state_t ;
struct TYPE_15__ {int unicast; struct TYPE_15__* next; } ;
typedef  TYPE_4__ mdns_out_question_t ;
struct TYPE_16__ {TYPE_1__* interfaces; } ;
struct TYPE_12__ {TYPE_3__* pcbs; } ;

/* Variables and functions */
#define  PCB_ANNOUNCE_1 133 
#define  PCB_ANNOUNCE_2 132 
#define  PCB_ANNOUNCE_3 131 
 int PCB_OFF ; 
#define  PCB_PROBE_1 130 
#define  PCB_PROBE_2 129 
#define  PCB_PROBE_3 128 
 int PCB_RUNNING ; 
 TYPE_2__* _mdns_create_announce_from_probe (TYPE_2__*) ; 
 int /*<<< orphan*/  _mdns_dispatch_tx_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  _mdns_free_tx_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  _mdns_schedule_tx_packet (TYPE_2__*,int) ; 
 TYPE_6__* _mdns_server ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _mdns_tx_handle_packet(mdns_tx_packet_t * p)
{
    mdns_tx_packet_t * a = NULL;
    mdns_out_question_t * q = NULL;
    mdns_pcb_t * pcb = &_mdns_server->interfaces[p->tcpip_if].pcbs[p->ip_protocol];
    uint32_t send_after = 1000;

    if (pcb->state == PCB_OFF) {
        _mdns_free_tx_packet(p);
        return;
    }
    _mdns_dispatch_tx_packet(p);

    switch(pcb->state) {
    case PCB_PROBE_1:
        q = p->questions;
        while (q) {
            q->unicast = false;
            q = q->next;
        }
        //fallthrough
    case PCB_PROBE_2:
        _mdns_schedule_tx_packet(p, 250);
        pcb->state = (mdns_pcb_state_t)((uint8_t)(pcb->state) + 1);
        break;
    case PCB_PROBE_3:
        a = _mdns_create_announce_from_probe(p);
        if (!a) {
            _mdns_schedule_tx_packet(p, 250);
            break;
        }
        pcb->probe_running = false;
        pcb->probe_ip = false;
        pcb->probe_services_len = 0;
        pcb->failed_probes = 0;
        free(pcb->probe_services);
        pcb->probe_services = NULL;
        _mdns_free_tx_packet(p);
        p = a;
        send_after = 250;
        //fallthrough
    case PCB_ANNOUNCE_1:
        //fallthrough
    case PCB_ANNOUNCE_2:
        _mdns_schedule_tx_packet(p, send_after);
        pcb->state = (mdns_pcb_state_t)((uint8_t)(pcb->state) + 1);
        break;
    case PCB_ANNOUNCE_3:
        pcb->state = PCB_RUNNING;
        _mdns_free_tx_packet(p);
        break;
    default:
        _mdns_free_tx_packet(p);
        break;
    }
}