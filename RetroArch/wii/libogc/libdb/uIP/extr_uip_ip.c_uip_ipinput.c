#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16_t ;
struct uip_pbuf {int len; struct uip_ip_hdr* payload; } ;
struct uip_netif {int /*<<< orphan*/  ip_addr; struct uip_netif* next; } ;
struct uip_ip_hdr {int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  s8_t ;
struct TYPE_3__ {int /*<<< orphan*/  drop; int /*<<< orphan*/  chkerr; } ;
struct TYPE_4__ {TYPE_1__ ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERROR (char*) ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 int /*<<< orphan*/  UIP_ICMP_DUR_PROTO ; 
 int UIP_IPH_HL (struct uip_ip_hdr*) ; 
 int /*<<< orphan*/  UIP_IPH_LEN (struct uip_ip_hdr*) ; 
 int UIP_IPH_OFFSET (struct uip_ip_hdr*) ; 
 int UIP_IPH_PROTO (struct uip_ip_hdr*) ; 
 int UIP_IPH_V (struct uip_ip_hdr*) ; 
 int UIP_IP_MF ; 
 int UIP_IP_OFFMASK ; 
 int /*<<< orphan*/  UIP_LOG (char*) ; 
#define  UIP_PROTO_ICMP 129 
#define  UIP_PROTO_TCP 128 
 int /*<<< orphan*/  UIP_STAT (int /*<<< orphan*/ ) ; 
 int htons (int) ; 
 scalar_t__ ip_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_addr_isany (int /*<<< orphan*/ *) ; 
 scalar_t__ ip_addr_isbroadcast (int /*<<< orphan*/ *,struct uip_netif*) ; 
 int /*<<< orphan*/  ip_addr_ismulticast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_icmp_destunreach (struct uip_pbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_icmpinput (struct uip_pbuf*,struct uip_netif*) ; 
 scalar_t__ uip_ipchksum (struct uip_ip_hdr*,int) ; 
 struct uip_pbuf* uip_ipreass (struct uip_pbuf*) ; 
 scalar_t__ uip_netif_isup (struct uip_netif*) ; 
 struct uip_netif* uip_netif_list ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 int /*<<< orphan*/  uip_pbuf_realloc (struct uip_pbuf*,int /*<<< orphan*/ ) ; 
 TYPE_2__ uip_stat ; 
 int /*<<< orphan*/  uip_tcpinput (struct uip_pbuf*,struct uip_netif*) ; 

s8_t uip_ipinput(struct uip_pbuf *p,struct uip_netif *inp)
{
	u16_t iphdr_len;
	struct uip_ip_hdr *iphdr;
	struct uip_netif *netif;

	iphdr = p->payload;
	if(UIP_IPH_V(iphdr)!=4) {
		UIP_ERROR("uip_ipinput: ip packet dropped due to bad version number.\n");
		uip_pbuf_free(p);
		return 0;
	}

	iphdr_len = UIP_IPH_HL(iphdr);
	iphdr_len *= 4;

	if(iphdr_len>p->len) {
		UIP_ERROR("uip_ipinput: ip packet dropped due to too small packet size.\n");
		uip_pbuf_free(p);
		return 0;
	}

	if(uip_ipchksum(iphdr,iphdr_len)!=0) {
	    UIP_STAT(++uip_stat.ip.drop);
	    UIP_STAT(++uip_stat.ip.chkerr);
		UIP_ERROR("uip_ipinput: bad checksum.\n");
		uip_pbuf_free(p);
		return 0;
	}

	uip_pbuf_realloc(p,ntohs(UIP_IPH_LEN(iphdr)));

	for(netif=uip_netif_list;netif!=NULL;netif=netif->next) {
		if(uip_netif_isup(netif) && !ip_addr_isany(&netif->ip_addr)) {
			if(ip_addr_cmp(&iphdr->dst,&netif->ip_addr) ||
				ip_addr_isbroadcast(&iphdr->dst,netif)) break;
		}
	}

	if(!netif) {
		UIP_ERROR("uip_ipinput: no route found.\n");
		uip_pbuf_free(p);
		return 0;
	}

	if((UIP_IPH_OFFSET(iphdr)&htons(UIP_IP_OFFMASK|UIP_IP_MF))!=0) {
#if UIP_IP_REASSEMBLY
		p = uip_ipreass(p);
		if(p==NULL) return UIP_ERR_OK;

		iphdr = (struct uip_ip_hdr*)p->payload;
#else
		uip_pbuf_free(p);
	    UIP_STAT(++uip_stat.ip.drop);
		UIP_ERROR("ip: fragment dropped.\n");
		return 0;
#endif
	}

	switch(UIP_IPH_PROTO(iphdr)) {
		case UIP_PROTO_TCP:
			uip_tcpinput(p,inp);
			break;
		case UIP_PROTO_ICMP:
			uip_icmpinput(p,inp);
			break;
		default:
			UIP_LOG("uip_ipinput: Unsupported protocol.\n");
			if(!ip_addr_isbroadcast(&(iphdr->dst),inp)
				&& !ip_addr_ismulticast(&(iphdr->dst))) {
				p->payload = iphdr;
				uip_icmp_destunreach(p,UIP_ICMP_DUR_PROTO);
			}
			uip_pbuf_free(p);
			break;
	}
	return 0;
}