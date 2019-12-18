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
struct nlattr {int dummy; } ;
struct ip_vs_flags {int mask; int flags; } ;
struct ip_vs_service_user_kern {int flags; void* netmask; void* timeout; int /*<<< orphan*/ * pe_name; int /*<<< orphan*/ * sched_name; void* port; struct ip_vs_flags addr; void* protocol; void* af; void* fwmark; } ;
struct ip_vs_service {int flags; } ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 void* IPPROTO_TCP ; 
 size_t IPVS_SVC_ATTR_ADDR ; 
 size_t IPVS_SVC_ATTR_AF ; 
 size_t IPVS_SVC_ATTR_FLAGS ; 
 size_t IPVS_SVC_ATTR_FWMARK ; 
 int /*<<< orphan*/  IPVS_SVC_ATTR_MAX ; 
 size_t IPVS_SVC_ATTR_NETMASK ; 
 size_t IPVS_SVC_ATTR_PE_NAME ; 
 size_t IPVS_SVC_ATTR_PORT ; 
 size_t IPVS_SVC_ATTR_PROTOCOL ; 
 size_t IPVS_SVC_ATTR_SCHED_NAME ; 
 size_t IPVS_SVC_ATTR_TIMEOUT ; 
 struct ip_vs_service* __ip_vs_service_get (void*,void*,struct ip_vs_flags*,void*) ; 
 struct ip_vs_service* __ip_vs_svc_fwm_get (void*,void*) ; 
 int /*<<< orphan*/  ip_vs_service_put (struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_svc_policy ; 
 int /*<<< orphan*/  memset (struct ip_vs_service_user_kern*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 void* nla_get_u16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (struct ip_vs_flags*,struct nlattr*,int) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_parse_service(struct ip_vs_service_user_kern *usvc,
				    struct nlattr *nla, int full_entry)
{
	struct nlattr *attrs[IPVS_SVC_ATTR_MAX + 1];
	struct nlattr *nla_af, *nla_port, *nla_fwmark, *nla_protocol, *nla_addr;

	/* Parse mandatory identifying service fields first */
	if (nla == NULL ||
	    nla_parse_nested(attrs, IPVS_SVC_ATTR_MAX, nla, ip_vs_svc_policy))
		return -EINVAL;

	nla_af		= attrs[IPVS_SVC_ATTR_AF];
	nla_protocol	= attrs[IPVS_SVC_ATTR_PROTOCOL];
	nla_addr	= attrs[IPVS_SVC_ATTR_ADDR];
	nla_port	= attrs[IPVS_SVC_ATTR_PORT];
	nla_fwmark	= attrs[IPVS_SVC_ATTR_FWMARK];

	if (!(nla_af && (nla_fwmark || (nla_port && nla_protocol && nla_addr))))
		return -EINVAL;

	memset(usvc, 0, sizeof(*usvc));

	usvc->af = nla_get_u16(nla_af);
#ifdef CONFIG_IP_VS_IPV6
	if (usvc->af != AF_INET && usvc->af != AF_INET6)
#else
	if (usvc->af != AF_INET)
#endif
		return -EAFNOSUPPORT;

	if (nla_fwmark) {
		usvc->protocol = IPPROTO_TCP;
		usvc->fwmark = nla_get_u32(nla_fwmark);
	} else {
		usvc->protocol = nla_get_u16(nla_protocol);
		nla_memcpy(&usvc->addr, nla_addr, sizeof(usvc->addr));
		usvc->port = nla_get_u16(nla_port);
		usvc->fwmark = 0;
	}

	/* If a full entry was requested, check for the additional fields */
	if (full_entry) {
		struct nlattr *nla_sched, *nla_flags, *nla_pe, *nla_timeout,
			      *nla_netmask;
		struct ip_vs_flags flags;
		struct ip_vs_service *svc;

		nla_sched = attrs[IPVS_SVC_ATTR_SCHED_NAME];
		nla_pe = attrs[IPVS_SVC_ATTR_PE_NAME];
		nla_flags = attrs[IPVS_SVC_ATTR_FLAGS];
		nla_timeout = attrs[IPVS_SVC_ATTR_TIMEOUT];
		nla_netmask = attrs[IPVS_SVC_ATTR_NETMASK];

		if (!(nla_sched && nla_flags && nla_timeout && nla_netmask))
			return -EINVAL;

		nla_memcpy(&flags, nla_flags, sizeof(flags));

		/* prefill flags from service if it already exists */
		if (usvc->fwmark)
			svc = __ip_vs_svc_fwm_get(usvc->af, usvc->fwmark);
		else
			svc = __ip_vs_service_get(usvc->af, usvc->protocol,
						  &usvc->addr, usvc->port);
		if (svc) {
			usvc->flags = svc->flags;
			ip_vs_service_put(svc);
		} else
			usvc->flags = 0;

		/* set new flags from userland */
		usvc->flags = (usvc->flags & ~flags.mask) |
			      (flags.flags & flags.mask);
		usvc->sched_name = nla_data(nla_sched);
		usvc->pe_name = nla_pe ? nla_data(nla_pe) : NULL;
		usvc->timeout = nla_get_u32(nla_timeout);
		usvc->netmask = nla_get_u32(nla_netmask);
	}

	return 0;
}