#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct udp_pcb {int dummy; } ;
struct pbuf {scalar_t__ payload; struct pbuf* next; } ;
struct TYPE_25__ {int addr; } ;
struct TYPE_26__ {TYPE_13__ ip4; } ;
struct TYPE_27__ {TYPE_14__ u_addr; } ;
struct TYPE_22__ {int addr; } ;
struct TYPE_23__ {TYPE_10__ ip4; } ;
struct TYPE_24__ {TYPE_11__ u_addr; } ;
struct netif {TYPE_15__ netmask; TYPE_12__ ip_addr; } ;
struct TYPE_33__ {int /*<<< orphan*/  addr; } ;
struct ip_hdr {TYPE_2__ dest; } ;
struct TYPE_36__ {scalar_t__ addr; } ;
struct ip6_hdr {TYPE_5__ dest; } ;
struct TYPE_39__ {int addr; } ;
struct TYPE_40__ {TYPE_8__ ip4; } ;
struct TYPE_29__ {scalar_t__ type; TYPE_9__ u_addr; } ;
struct TYPE_34__ {TYPE_17__ addr; } ;
struct TYPE_31__ {int /*<<< orphan*/  addr; } ;
struct TYPE_35__ {TYPE_3__ ip6; TYPE_1__ ip4; } ;
struct TYPE_30__ {scalar_t__ type; TYPE_4__ u_addr; } ;
struct TYPE_28__ {size_t tcpip_if; size_t ip_protocol; TYPE_17__ src; TYPE_18__ dest; int /*<<< orphan*/  multicast; struct pbuf* pb; int /*<<< orphan*/  src_port; } ;
typedef  TYPE_16__ mdns_rx_packet_t ;
typedef  size_t ip_addr_t ;
struct TYPE_38__ {TYPE_6__* pcbs; } ;
struct TYPE_37__ {struct udp_pcb* pcb; } ;
struct TYPE_32__ {int /*<<< orphan*/  action_queue; TYPE_7__* interfaces; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 int IP6_HLEN ; 
 scalar_t__ IPADDR_TYPE_V4 ; 
 int IP_HLEN ; 
 size_t MDNS_IF_MAX ; 
 size_t MDNS_IP_PROTOCOL_V4 ; 
 size_t MDNS_IP_PROTOCOL_V6 ; 
 size_t* UDP_HLEN ; 
 int /*<<< orphan*/  _mdns_get_esp_netif (size_t) ; 
 scalar_t__ _mdns_send_rx_action (TYPE_16__*) ; 
 TYPE_20__* _mdns_server ; 
 struct netif* esp_netif_get_netif_impl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_16__*) ; 
 int /*<<< orphan*/  ip_addr_ismulticast (TYPE_18__*) ; 
 struct netif* ip_current_input_netif () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_17__*,size_t const*,int) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

__attribute__((used)) static void _udp_recv(void *arg, struct udp_pcb *upcb, struct pbuf *pb, const ip_addr_t *raddr, uint16_t rport)
{

    uint8_t i;
    while (pb != NULL) {
        struct pbuf * this_pb = pb;
        pb = pb->next;
        this_pb->next = NULL;

        mdns_rx_packet_t * packet = (mdns_rx_packet_t *)malloc(sizeof(mdns_rx_packet_t));
        if (!packet) {
            HOOK_MALLOC_FAILED;
            //missed packet - no memory
            pbuf_free(this_pb);
            continue;
        }

        packet->tcpip_if = MDNS_IF_MAX;
        packet->pb = this_pb;
        packet->src_port = rport;
        memcpy(&packet->src, raddr, sizeof(ip_addr_t));
        packet->dest.type = packet->src.type;

        if (packet->src.type == IPADDR_TYPE_V4) {
            packet->ip_protocol = MDNS_IP_PROTOCOL_V4;
            struct ip_hdr * iphdr = (struct ip_hdr *)(((uint8_t *)(packet->pb->payload)) - UDP_HLEN - IP_HLEN);
            packet->dest.u_addr.ip4.addr = iphdr->dest.addr;
        } else {
            packet->ip_protocol = MDNS_IP_PROTOCOL_V6;
            struct ip6_hdr * ip6hdr = (struct ip6_hdr *)(((uint8_t *)(packet->pb->payload)) - UDP_HLEN - IP6_HLEN);
            memcpy(&packet->dest.u_addr.ip6.addr, (uint8_t *)ip6hdr->dest.addr, 16);
        }
        packet->multicast = ip_addr_ismulticast(&(packet->dest));

        //lwip does not return the proper pcb if you have more than one for the same multicast address (but different interfaces)
        struct netif * netif = NULL;
        struct udp_pcb * pcb = NULL;
        for (i=0; i<MDNS_IF_MAX; i++) {
            pcb = _mdns_server->interfaces[i].pcbs[packet->ip_protocol].pcb;
            netif = esp_netif_get_netif_impl(_mdns_get_esp_netif(i));
            if (pcb && netif && netif == ip_current_input_netif ()) {
                if (packet->src.type == IPADDR_TYPE_V4) {
                    if ((packet->src.u_addr.ip4.addr & netif->netmask.u_addr.ip4.addr) != (netif->ip_addr.u_addr.ip4.addr & netif->netmask.u_addr.ip4.addr)) {
                        //packet source is not in the same subnet
                        pcb = NULL;
                        break;
                    }
                }
                packet->tcpip_if = i;
                break;
            }
            pcb = NULL;
        }

        if (!pcb || !_mdns_server || !_mdns_server->action_queue
          || _mdns_send_rx_action(packet) != ESP_OK) {
            pbuf_free(this_pb);
            free(packet);
        }
    }

}