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
union nf_inet_addr {int ip; int /*<<< orphan*/  in6; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct ip_vs_service {scalar_t__ af; int netmask; scalar_t__ port; int flags; int /*<<< orphan*/  timeout; TYPE_1__* scheduler; scalar_t__ fwmark; } ;
struct ip_vs_iphdr {int protocol; union nf_inet_addr daddr; union nf_inet_addr saddr; } ;
struct ip_vs_dest {scalar_t__ port; int /*<<< orphan*/  addr; } ;
struct ip_vs_conn_param {int /*<<< orphan*/  pe_data; } ;
struct ip_vs_conn {struct ip_vs_dest* dest; int /*<<< orphan*/  timeout; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {struct ip_vs_dest* (* schedule ) (struct ip_vs_service*,struct sk_buff*) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ FTPPORT ; 
 int IPPROTO_IP ; 
 int IPPROTO_UDP ; 
 unsigned int IP_VS_CONN_F_ONE_PACKET ; 
 unsigned int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*) ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (scalar_t__,union nf_inet_addr*) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_SVC_F_ONEPACKET ; 
 int htonl (scalar_t__) ; 
 int /*<<< orphan*/  ip_vs_check_template (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param (scalar_t__,int,union nf_inet_addr*,scalar_t__,union nf_inet_addr*,scalar_t__,struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param_persist (struct ip_vs_service*,struct sk_buff*,int,union nf_inet_addr*,int /*<<< orphan*/ ,union nf_inet_addr const*,scalar_t__,struct ip_vs_conn_param*) ; 
 struct ip_vs_conn* ip_vs_conn_new (struct ip_vs_conn_param*,int /*<<< orphan*/ *,scalar_t__,unsigned int,struct ip_vs_dest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_stats (struct ip_vs_conn*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_control_add (struct ip_vs_conn*,struct ip_vs_conn*) ; 
 struct ip_vs_conn* ip_vs_ct_in_get (struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  ip_vs_fill_iphdr (scalar_t__,int /*<<< orphan*/ ,struct ip_vs_iphdr*) ; 
 int /*<<< orphan*/  ipv6_addr_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 
 struct ip_vs_dest* stub1 (struct ip_vs_service*,struct sk_buff*) ; 

__attribute__((used)) static struct ip_vs_conn *
ip_vs_sched_persist(struct ip_vs_service *svc,
		    struct sk_buff *skb,
		    __be16 src_port, __be16 dst_port)
{
	struct ip_vs_conn *cp = NULL;
	struct ip_vs_iphdr iph;
	struct ip_vs_dest *dest;
	struct ip_vs_conn *ct;
	__be16 dport = 0;		/* destination port to forward */
	unsigned int flags;
	struct ip_vs_conn_param param;
	const union nf_inet_addr fwmark = { .ip = htonl(svc->fwmark) };
	union nf_inet_addr snet;	/* source network of the client,
					   after masking */

	ip_vs_fill_iphdr(svc->af, skb_network_header(skb), &iph);

	/* Mask saddr with the netmask to adjust template granularity */
#ifdef CONFIG_IP_VS_IPV6
	if (svc->af == AF_INET6)
		ipv6_addr_prefix(&snet.in6, &iph.saddr.in6, svc->netmask);
	else
#endif
		snet.ip = iph.saddr.ip & svc->netmask;

	IP_VS_DBG_BUF(6, "p-schedule: src %s:%u dest %s:%u "
		      "mnet %s\n",
		      IP_VS_DBG_ADDR(svc->af, &iph.saddr), ntohs(src_port),
		      IP_VS_DBG_ADDR(svc->af, &iph.daddr), ntohs(dst_port),
		      IP_VS_DBG_ADDR(svc->af, &snet));

	/*
	 * As far as we know, FTP is a very complicated network protocol, and
	 * it uses control connection and data connections. For active FTP,
	 * FTP server initialize data connection to the client, its source port
	 * is often 20. For passive FTP, FTP server tells the clients the port
	 * that it passively listens to,  and the client issues the data
	 * connection. In the tunneling or direct routing mode, the load
	 * balancer is on the client-to-server half of connection, the port
	 * number is unknown to the load balancer. So, a conn template like
	 * <caddr, 0, vaddr, 0, daddr, 0> is created for persistent FTP
	 * service, and a template like <caddr, 0, vaddr, vport, daddr, dport>
	 * is created for other persistent services.
	 */
	{
		int protocol = iph.protocol;
		const union nf_inet_addr *vaddr = &iph.daddr;
		__be16 vport = 0;

		if (dst_port == svc->port) {
			/* non-FTP template:
			 * <protocol, caddr, 0, vaddr, vport, daddr, dport>
			 * FTP template:
			 * <protocol, caddr, 0, vaddr, 0, daddr, 0>
			 */
			if (svc->port != FTPPORT)
				vport = dst_port;
		} else {
			/* Note: persistent fwmark-based services and
			 * persistent port zero service are handled here.
			 * fwmark template:
			 * <IPPROTO_IP,caddr,0,fwmark,0,daddr,0>
			 * port zero template:
			 * <protocol,caddr,0,vaddr,0,daddr,0>
			 */
			if (svc->fwmark) {
				protocol = IPPROTO_IP;
				vaddr = &fwmark;
			}
		}
		ip_vs_conn_fill_param_persist(svc, skb, protocol, &snet, 0,
					      vaddr, vport, &param);
	}

	/* Check if a template already exists */
	ct = ip_vs_ct_in_get(&param);
	if (!ct || !ip_vs_check_template(ct)) {
		/* No template found or the dest of the connection
		 * template is not available.
		 */
		dest = svc->scheduler->schedule(svc, skb);
		if (!dest) {
			IP_VS_DBG(1, "p-schedule: no dest found.\n");
			kfree(param.pe_data);
			return NULL;
		}

		if (dst_port == svc->port && svc->port != FTPPORT)
			dport = dest->port;

		/* Create a template
		 * This adds param.pe_data to the template,
		 * and thus param.pe_data will be destroyed
		 * when the template expires */
		ct = ip_vs_conn_new(&param, &dest->addr, dport,
				    IP_VS_CONN_F_TEMPLATE, dest, skb->mark);
		if (ct == NULL) {
			kfree(param.pe_data);
			return NULL;
		}

		ct->timeout = svc->timeout;
	} else {
		/* set destination with the found template */
		dest = ct->dest;
		kfree(param.pe_data);
	}

	dport = dst_port;
	if (dport == svc->port && dest->port)
		dport = dest->port;

	flags = (svc->flags & IP_VS_SVC_F_ONEPACKET
		 && iph.protocol == IPPROTO_UDP)?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Create a new connection according to the template
	 */
	ip_vs_conn_fill_param(svc->af, iph.protocol, &iph.saddr, src_port,
			      &iph.daddr, dst_port, &param);

	cp = ip_vs_conn_new(&param, &dest->addr, dport, flags, dest, skb->mark);
	if (cp == NULL) {
		ip_vs_conn_put(ct);
		return NULL;
	}

	/*
	 *    Add its control
	 */
	ip_vs_control_add(cp, ct);
	ip_vs_conn_put(ct);

	ip_vs_conn_stats(cp, svc);
	return cp;
}