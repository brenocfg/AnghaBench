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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int dummy; } ;
struct ip_vs_service {TYPE_1__* pe; int /*<<< orphan*/  af; } ;
struct ip_vs_conn_param {TYPE_1__* pe; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* fill_param ) (struct ip_vs_conn_param*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_conn_fill_param (int /*<<< orphan*/ ,int,union nf_inet_addr const*,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_conn_param*,struct sk_buff*) ; 

__attribute__((used)) static inline void
ip_vs_conn_fill_param_persist(const struct ip_vs_service *svc,
			      struct sk_buff *skb, int protocol,
			      const union nf_inet_addr *caddr, __be16 cport,
			      const union nf_inet_addr *vaddr, __be16 vport,
			      struct ip_vs_conn_param *p)
{
	ip_vs_conn_fill_param(svc->af, protocol, caddr, cport, vaddr, vport, p);
	p->pe = svc->pe;
	if (p->pe && p->pe->fill_param)
		p->pe->fill_param(p, skb);
}