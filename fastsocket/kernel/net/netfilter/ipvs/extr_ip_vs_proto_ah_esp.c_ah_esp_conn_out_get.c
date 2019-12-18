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
struct sk_buff {int dummy; } ;
struct ip_vs_protocol {int /*<<< orphan*/  name; } ;
struct ip_vs_iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_vs_conn_param {int dummy; } ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ah_esp_conn_fill_param_proto (int,struct ip_vs_iphdr const*,int,struct ip_vs_conn_param*) ; 
 struct ip_vs_conn* ip_vs_conn_out_get (struct ip_vs_conn_param*) ; 

__attribute__((used)) static struct ip_vs_conn *
ah_esp_conn_out_get(int af, const struct sk_buff *skb,
		    struct ip_vs_protocol *pp,
		    const struct ip_vs_iphdr *iph,
		    unsigned int proto_off,
		    int inverse)
{
	struct ip_vs_conn *cp;
	struct ip_vs_conn_param p;

	ah_esp_conn_fill_param_proto(af, iph, inverse, &p);
	cp = ip_vs_conn_out_get(&p);
	if (!cp) {
		IP_VS_DBG_BUF(12, "Unknown ISAKMP entry for inout packet "
			      "%s%s %s->%s\n",
			      inverse ? "ICMP+" : "",
			      pp->name,
			      IP_VS_DBG_ADDR(af, &iph->saddr),
			      IP_VS_DBG_ADDR(af, &iph->daddr));
	}

	return cp;
}