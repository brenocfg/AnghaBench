#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct udphdr {int /*<<< orphan*/  dest; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct ip_vs_service {int dummy; } ;
struct ip_vs_protocol {int dummy; } ;
struct ip_vs_iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  len; } ;
struct ip_vs_conn {int dummy; } ;
typedef  int /*<<< orphan*/  _udph ;

/* Variables and functions */
 int NF_DROP ; 
 int /*<<< orphan*/  ip_vs_fill_iphdr (int,int /*<<< orphan*/ ,struct ip_vs_iphdr*) ; 
 int ip_vs_leave (struct ip_vs_service*,struct sk_buff*,struct ip_vs_protocol*) ; 
 struct ip_vs_conn* ip_vs_schedule (struct ip_vs_service*,struct sk_buff*) ; 
 struct ip_vs_service* ip_vs_service_get (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_service_put (struct ip_vs_service*) ; 
 scalar_t__ ip_vs_todrop () ; 
 struct udphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct udphdr*) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int
udp_conn_schedule(int af, struct sk_buff *skb, struct ip_vs_protocol *pp,
		  int *verdict, struct ip_vs_conn **cpp)
{
	struct ip_vs_service *svc;
	struct udphdr _udph, *uh;
	struct ip_vs_iphdr iph;

	ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);

	uh = skb_header_pointer(skb, iph.len, sizeof(_udph), &_udph);
	if (uh == NULL) {
		*verdict = NF_DROP;
		return 0;
	}

	svc = ip_vs_service_get(af, skb->mark, iph.protocol,
				&iph.daddr, uh->dest);
	if (svc) {
		if (ip_vs_todrop()) {
			/*
			 * It seems that we are very loaded.
			 * We have to drop this packet :(
			 */
			ip_vs_service_put(svc);
			*verdict = NF_DROP;
			return 0;
		}

		/*
		 * Let the virtual server select a real server for the
		 * incoming connection, and create a connection entry.
		 */
		*cpp = ip_vs_schedule(svc, skb);
		if (!*cpp) {
			*verdict = ip_vs_leave(svc, skb, pp);
			return 0;
		}
		ip_vs_service_put(svc);
	}
	return 1;
}