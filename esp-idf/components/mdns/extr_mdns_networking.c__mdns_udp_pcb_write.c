#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pbuf {scalar_t__ payload; } ;
typedef  int /*<<< orphan*/  mdns_ip_protocol_t ;
typedef  int /*<<< orphan*/  mdns_if_t ;
struct TYPE_2__ {scalar_t__ err; int /*<<< orphan*/  call; int /*<<< orphan*/  port; int /*<<< orphan*/ * ip; struct pbuf* pbt; int /*<<< orphan*/  ip_protocol; int /*<<< orphan*/  tcpip_if; } ;
typedef  TYPE_1__ mdns_api_call_t ;
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  int /*<<< orphan*/  esp_ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_TRANSPORT ; 
 int /*<<< orphan*/  _mdns_udp_pcb_write_api ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpip_api_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

size_t _mdns_udp_pcb_write(mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol, const esp_ip_addr_t *ip, uint16_t port, uint8_t * data, size_t len)
{
    struct pbuf* pbt = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
    if (pbt == NULL) {
        return 0;
    }
    memcpy((uint8_t *)pbt->payload, data, len);

    mdns_api_call_t msg = {
        .tcpip_if = tcpip_if,
        .ip_protocol = ip_protocol,
        .pbt = pbt,
        .ip = (ip_addr_t *)ip,
        .port = port
    };
    tcpip_api_call(_mdns_udp_pcb_write_api, &msg.call);

    if (msg.err) {
        return 0;
    }
    return len;
}