#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  answers; int /*<<< orphan*/  additional; } ;
typedef  TYPE_2__ mdns_tx_packet_t ;
struct TYPE_16__ {int /*<<< orphan*/ * service; } ;
typedef  TYPE_3__ mdns_srv_item_t ;
struct TYPE_17__ {scalar_t__ state; scalar_t__ pcb; } ;
typedef  TYPE_4__ mdns_pcb_t ;
typedef  size_t mdns_ip_protocol_t ;
typedef  size_t mdns_if_t ;
struct TYPE_18__ {int /*<<< orphan*/  hostname; TYPE_1__* interfaces; } ;
struct TYPE_14__ {TYPE_4__* pcbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDNS_TYPE_A ; 
 int /*<<< orphan*/  MDNS_TYPE_AAAA ; 
 int /*<<< orphan*/  MDNS_TYPE_PTR ; 
 int /*<<< orphan*/  MDNS_TYPE_SDPTR ; 
 int /*<<< orphan*/  MDNS_TYPE_SRV ; 
 int /*<<< orphan*/  MDNS_TYPE_TXT ; 
 void* PCB_ANNOUNCE_1 ; 
 scalar_t__ PCB_RUNNING ; 
 scalar_t__ PCB_STATE_IS_ANNOUNCING (TYPE_4__*) ; 
 scalar_t__ PCB_STATE_IS_PROBING (TYPE_4__*) ; 
 int /*<<< orphan*/  _mdns_alloc_answer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__* _mdns_create_announce_packet (size_t,size_t,TYPE_3__**,size_t,int) ; 
 int /*<<< orphan*/  _mdns_dealloc_answer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* _mdns_get_next_pcb_packet (size_t,size_t) ; 
 int /*<<< orphan*/  _mdns_init_pcb_probe (size_t,size_t,TYPE_3__**,size_t,int) ; 
 int /*<<< orphan*/  _mdns_schedule_tx_packet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* _mdns_server ; 
 scalar_t__ _str_null_or_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _mdns_announce_pcb(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol, mdns_srv_item_t ** services, size_t len, bool include_ip)
{
    mdns_pcb_t * _pcb = &_mdns_server->interfaces[tcpip_if].pcbs[ip_protocol];
    size_t i;
    if (_pcb->pcb) {
        if (PCB_STATE_IS_PROBING(_pcb)) {
            _mdns_init_pcb_probe(tcpip_if, ip_protocol, services, len, include_ip);
        } else if (PCB_STATE_IS_ANNOUNCING(_pcb)) {
            mdns_tx_packet_t *  p = _mdns_get_next_pcb_packet(tcpip_if, ip_protocol);
            if (p) {
                for (i=0; i<len; i++) {
                    if (!_mdns_alloc_answer(&p->answers, MDNS_TYPE_SDPTR, services[i]->service, false, false)
                            || !_mdns_alloc_answer(&p->answers, MDNS_TYPE_PTR, services[i]->service, false, false)
                            || !_mdns_alloc_answer(&p->answers, MDNS_TYPE_SRV, services[i]->service, true, false)
                            || !_mdns_alloc_answer(&p->answers, MDNS_TYPE_TXT, services[i]->service, true, false)) {
                        break;
                    }
                }
                if (include_ip) {
                    _mdns_dealloc_answer(&p->additional, MDNS_TYPE_A, NULL);
                    _mdns_dealloc_answer(&p->additional, MDNS_TYPE_AAAA, NULL);
                    _mdns_alloc_answer(&p->answers, MDNS_TYPE_A, NULL, true, false);
                    _mdns_alloc_answer(&p->answers, MDNS_TYPE_AAAA, NULL, true, false);
                }
                _pcb->state = PCB_ANNOUNCE_1;
            }
        } else if (_pcb->state == PCB_RUNNING) {

            if (_str_null_or_empty(_mdns_server->hostname)) {
                return;
            }

            _pcb->state = PCB_ANNOUNCE_1;
            mdns_tx_packet_t *  p = _mdns_create_announce_packet(tcpip_if, ip_protocol, services, len, include_ip);
            if (p) {
                _mdns_schedule_tx_packet(p, 0);
            }
        }
    }
}