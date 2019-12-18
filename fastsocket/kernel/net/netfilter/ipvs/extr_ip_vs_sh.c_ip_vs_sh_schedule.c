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
struct ip_vs_sh_bucket {int dummy; } ;
struct ip_vs_service {int /*<<< orphan*/  af; scalar_t__ sched_data; } ;
struct ip_vs_iphdr {int /*<<< orphan*/  saddr; } ;
struct ip_vs_dest {int flags; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG (int,char*) ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_DEST_F_AVAILABLE ; 
 int /*<<< orphan*/  IP_VS_ERR_RL (char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_fill_iphdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_vs_iphdr*) ; 
 struct ip_vs_dest* ip_vs_sh_get (int /*<<< orphan*/ ,struct ip_vs_sh_bucket*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_overloaded (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff const*) ; 

__attribute__((used)) static struct ip_vs_dest *
ip_vs_sh_schedule(struct ip_vs_service *svc, const struct sk_buff *skb)
{
	struct ip_vs_dest *dest;
	struct ip_vs_sh_bucket *tbl;
	struct ip_vs_iphdr iph;

	ip_vs_fill_iphdr(svc->af, skb_network_header(skb), &iph);

	IP_VS_DBG(6, "ip_vs_sh_schedule(): Scheduling...\n");

	tbl = (struct ip_vs_sh_bucket *)svc->sched_data;
	dest = ip_vs_sh_get(svc->af, tbl, &iph.saddr);
	if (!dest
	    || !(dest->flags & IP_VS_DEST_F_AVAILABLE)
	    || atomic_read(&dest->weight) <= 0
	    || is_overloaded(dest)) {
		IP_VS_ERR_RL("SH: no destination available\n");
		return NULL;
	}

	IP_VS_DBG_BUF(6, "SH: source IP address %s --> server %s:%d\n",
		      IP_VS_DBG_ADDR(svc->af, &iph.saddr),
		      IP_VS_DBG_ADDR(svc->af, &dest->addr),
		      ntohs(dest->port));

	return dest;
}