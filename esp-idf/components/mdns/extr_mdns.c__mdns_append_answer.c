#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct esp_ip6_addr {scalar_t__ addr; } ;
struct TYPE_16__ {scalar_t__ type; int /*<<< orphan*/  bye; int /*<<< orphan*/  flush; TYPE_8__* service; int /*<<< orphan*/  custom_proto; int /*<<< orphan*/  custom_service; int /*<<< orphan*/  custom_instance; } ;
typedef  TYPE_4__ mdns_out_answer_t ;
typedef  size_t mdns_if_t ;
struct TYPE_13__ {int /*<<< orphan*/  addr; } ;
struct TYPE_17__ {TYPE_1__ ip; } ;
typedef  TYPE_5__ esp_netif_ip_info_t ;
struct TYPE_19__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  service; } ;
struct TYPE_18__ {TYPE_3__* interfaces; } ;
struct TYPE_15__ {TYPE_2__* pcbs; } ;
struct TYPE_14__ {scalar_t__ state; int /*<<< orphan*/  pcb; } ;

/* Variables and functions */
 size_t MDNS_IP_PROTOCOL_V4 ; 
 size_t MDNS_IP_PROTOCOL_V6 ; 
 scalar_t__ MDNS_TYPE_A ; 
 scalar_t__ MDNS_TYPE_AAAA ; 
 scalar_t__ MDNS_TYPE_PTR ; 
 scalar_t__ MDNS_TYPE_SDPTR ; 
 scalar_t__ MDNS_TYPE_SRV ; 
 scalar_t__ MDNS_TYPE_TXT ; 
 scalar_t__ PCB_DUP ; 
 scalar_t__ _ipv6_address_is_zero (struct esp_ip6_addr) ; 
 scalar_t__ _mdns_append_a_record (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _mdns_append_aaaa_record (int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _mdns_append_ptr_record (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _mdns_append_sdptr_record (int*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _mdns_append_srv_record (int*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _mdns_append_txt_record (int*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_get_esp_netif (size_t) ; 
 size_t _mdns_get_other_if (size_t) ; 
 int /*<<< orphan*/  _mdns_get_service_instance_name (TYPE_8__*) ; 
 int /*<<< orphan*/  _mdns_if_is_dup (size_t) ; 
 TYPE_7__* _mdns_server ; 
 scalar_t__ esp_netif_get_ip6_linklocal (int /*<<< orphan*/ ,struct esp_ip6_addr*) ; 
 scalar_t__ esp_netif_get_ip_info (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static uint8_t _mdns_append_answer(uint8_t * packet, uint16_t * index, mdns_out_answer_t * answer, mdns_if_t tcpip_if)
{
    if (answer->type == MDNS_TYPE_PTR) {

        if (answer->service) {
            return _mdns_append_ptr_record(packet, index,
                _mdns_get_service_instance_name(answer->service),
                answer->service->service, answer->service->proto,
                answer->flush, answer->bye) > 0;
        } else {
            return _mdns_append_ptr_record(packet, index,
                answer->custom_instance, answer->custom_service, answer->custom_proto,
                answer->flush, answer->bye) > 0;
        }
    } else if (answer->type == MDNS_TYPE_SRV) {
        return _mdns_append_srv_record(packet, index, answer->service, answer->flush, answer->bye) > 0;
    } else if (answer->type == MDNS_TYPE_TXT) {
        return _mdns_append_txt_record(packet, index, answer->service, answer->flush, answer->bye) > 0;
    } else if (answer->type == MDNS_TYPE_SDPTR) {
        return _mdns_append_sdptr_record(packet, index, answer->service, answer->flush, answer->bye) > 0;
    } else if (answer->type == MDNS_TYPE_A) {
        esp_netif_ip_info_t if_ip_info;
        if (!_mdns_server->interfaces[tcpip_if].pcbs[MDNS_IP_PROTOCOL_V4].pcb && _mdns_server->interfaces[tcpip_if].pcbs[MDNS_IP_PROTOCOL_V4].state != PCB_DUP) {
            return 0;
        }
        if (esp_netif_get_ip_info(_mdns_get_esp_netif(tcpip_if), &if_ip_info)) {
            return 0;
        }
        if (_mdns_append_a_record(packet, index, if_ip_info.ip.addr, answer->flush, answer->bye) <= 0) {
            return 0;
        }
        if (!_mdns_if_is_dup(tcpip_if)) {
            return 1;
        }
        mdns_if_t other_if = _mdns_get_other_if (tcpip_if);
        if (esp_netif_get_ip_info(_mdns_get_esp_netif(other_if), &if_ip_info)) {
            return 1;
        }
        if (_mdns_append_a_record(packet, index, if_ip_info.ip.addr, answer->flush, answer->bye) > 0) {
            return 2;
        }
        return 1;
    } else if (answer->type == MDNS_TYPE_AAAA) {
        struct esp_ip6_addr if_ip6;
        if (!_mdns_server->interfaces[tcpip_if].pcbs[MDNS_IP_PROTOCOL_V6].pcb && _mdns_server->interfaces[tcpip_if].pcbs[MDNS_IP_PROTOCOL_V6].state != PCB_DUP) {
            return 0;
        }
        if (esp_netif_get_ip6_linklocal(_mdns_get_esp_netif(tcpip_if), &if_ip6)) {
            return 0;
        }
        if (_ipv6_address_is_zero(if_ip6)) {
            return 0;
        }
        if (_mdns_append_aaaa_record(packet, index, (uint8_t*)if_ip6.addr, answer->flush, answer->bye) <= 0) {
            return 0;
        }
        if (!_mdns_if_is_dup(tcpip_if)) {
            return 1;
        }
        mdns_if_t other_if = _mdns_get_other_if (tcpip_if);
        if (esp_netif_get_ip6_linklocal(_mdns_get_esp_netif(other_if), &if_ip6)) {
            return 1;
        }
        if (_mdns_append_aaaa_record(packet, index, (uint8_t*)if_ip6.addr, answer->flush, answer->bye) > 0) {
            return 2;
        }
        return 1;
    }
    return 0;
}