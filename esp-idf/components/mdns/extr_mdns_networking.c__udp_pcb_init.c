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
typedef  scalar_t__ esp_err_t ;
struct TYPE_6__ {TYPE_1__* interfaces; } ;
struct TYPE_5__ {scalar_t__ failed_probes; scalar_t__ pcb; } ;
struct TYPE_4__ {TYPE_2__* pcbs; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 TYPE_3__* _mdns_server ; 
 scalar_t__ _pcb_main ; 
 scalar_t__ _udp_join_group (size_t,size_t,int) ; 
 scalar_t__ _udp_pcb_main_init () ; 

__attribute__((used)) static esp_err_t _udp_pcb_init(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    if (!_mdns_server || _mdns_server->interfaces[tcpip_if].pcbs[ip_protocol].pcb) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t err = _udp_join_group(tcpip_if, ip_protocol, true);
    if(err){
        return err;
    }

    err = _udp_pcb_main_init();
    if(err){
        return err;
    }

    _mdns_server->interfaces[tcpip_if].pcbs[ip_protocol].pcb = _pcb_main;
    _mdns_server->interfaces[tcpip_if].pcbs[ip_protocol].failed_probes = 0;
    return ESP_OK;
}