#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_19__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_17__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
union pf_state_xport {void* port; } ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct pfi_kif {int dummy; } ;
struct pf_src_node {int dummy; } ;
struct TYPE_36__ {int* proxy_port; int opts; TYPE_6__* cur; } ;
struct TYPE_27__ {void** port; } ;
struct TYPE_29__ {TYPE_17__ range; } ;
struct TYPE_30__ {int /*<<< orphan*/  s_addr; } ;
struct pf_addr {int /*<<< orphan*/ * addr32; TYPE_1__ v4addr; } ;
struct TYPE_24__ {int /*<<< orphan*/  mask; struct pf_addr addr; } ;
struct TYPE_25__ {TYPE_14__ a; } ;
struct TYPE_23__ {int /*<<< orphan*/ * dyn; } ;
struct TYPE_26__ {TYPE_15__ v; TYPE_13__ p; int /*<<< orphan*/  type; } ;
struct TYPE_28__ {TYPE_19__ xport; TYPE_16__ addr; } ;
struct TYPE_38__ {int /*<<< orphan*/  mask; struct pf_addr addr; } ;
struct TYPE_20__ {TYPE_9__ a; } ;
struct TYPE_37__ {int /*<<< orphan*/ * dyn; } ;
struct TYPE_21__ {TYPE_10__ v; TYPE_8__ p; int /*<<< orphan*/  type; } ;
struct TYPE_22__ {TYPE_11__ addr; } ;
struct pf_rule {int action; TYPE_7__ rpool; TYPE_18__ dst; TYPE_12__ src; } ;
struct pf_pdesc {int /*<<< orphan*/  af; int /*<<< orphan*/  naf; struct pf_addr ndaddr; struct pf_addr naddr; } ;
typedef  int /*<<< orphan*/  pbuf_t ;
struct TYPE_32__ {int /*<<< orphan*/  mask; struct pf_addr addr; } ;
struct TYPE_33__ {TYPE_3__ a; } ;
struct TYPE_31__ {int /*<<< orphan*/ * dyn; } ;
struct TYPE_34__ {TYPE_4__ v; TYPE_2__ p; int /*<<< orphan*/  type; } ;
struct TYPE_35__ {TYPE_5__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DPFPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PF_ADDR_DYNIFTL ; 
#define  PF_BINAT 137 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
#define  PF_IN 136 
#define  PF_NAT 135 
#define  PF_NAT64 134 
#define  PF_NOBINAT 133 
#define  PF_NONAT 132 
#define  PF_NONAT64 131 
#define  PF_NORDR 130 
#define  PF_OUT 129 
 int /*<<< orphan*/  PF_POOLMASK (struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ *,struct pf_addr*,int /*<<< orphan*/ ) ; 
 int PF_POOL_BITMASK ; 
 int PF_POOL_TYPEMASK ; 
#define  PF_RDR 128 
 int /*<<< orphan*/  PF_RULESET_BINAT ; 
 int /*<<< orphan*/  PF_RULESET_NAT ; 
 int /*<<< orphan*/  PF_RULESET_RDR ; 
 void* htons (int) ; 
 int ntohs (void*) ; 
 int /*<<< orphan*/  pf_get_sport (struct pf_pdesc*,struct pfi_kif*,struct pf_rule*,struct pf_addr*,union pf_state_xport*,struct pf_addr*,union pf_state_xport*,struct pf_addr*,union pf_state_xport*,struct pf_src_node**) ; 
 int /*<<< orphan*/  pf_map_addr (int /*<<< orphan*/ ,struct pf_rule*,struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ *,struct pf_src_node**) ; 
 struct pf_rule* pf_match_translation (struct pf_pdesc*,int /*<<< orphan*/ *,int,int,struct pfi_kif*,struct pf_addr*,union pf_state_xport*,struct pf_addr*,union pf_state_xport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pf_rule *
pf_get_translation_aux(struct pf_pdesc *pd, pbuf_t *pbuf, int off,
    int direction, struct pfi_kif *kif, struct pf_src_node **sn,
    struct pf_addr *saddr, union pf_state_xport *sxport, struct pf_addr *daddr,
    union pf_state_xport *dxport, union pf_state_xport *nsxport
    )
{
	struct pf_rule	*r = NULL;
	pd->naf = pd->af;

	if (direction == PF_OUT) {
		r = pf_match_translation(pd, pbuf, off, direction, kif, saddr,
		    sxport, daddr, dxport, PF_RULESET_BINAT);
		if (r == NULL)
			r = pf_match_translation(pd, pbuf, off, direction, kif,
			    saddr, sxport, daddr, dxport, PF_RULESET_RDR);
		if (r == NULL)
			r = pf_match_translation(pd, pbuf, off, direction, kif,
			    saddr, sxport, daddr, dxport, PF_RULESET_NAT);
	} else {
		r = pf_match_translation(pd, pbuf, off, direction, kif, saddr,
		    sxport, daddr, dxport, PF_RULESET_RDR);
		if (r == NULL)
			r = pf_match_translation(pd, pbuf, off, direction, kif,
			    saddr, sxport, daddr, dxport, PF_RULESET_BINAT);
	}

	if (r != NULL) {
		struct pf_addr *nsaddr = &pd->naddr;
		struct pf_addr *ndaddr = &pd->ndaddr;

		*nsaddr = *saddr;
		*ndaddr = *daddr;

		switch (r->action) {
		case PF_NONAT:
		case PF_NONAT64:
		case PF_NOBINAT:
		case PF_NORDR:
			return (NULL);
		case PF_NAT:
		case PF_NAT64:
			/*
			 * we do NAT64 on incoming path and we call ip_input
			 * which asserts receive interface to be not NULL.
			 * The below check is to prevent NAT64 action on any
			 * packet generated by local entity using synthesized
			 * IPv6 address.
			 */
			if ((r->action == PF_NAT64) && (direction == PF_OUT))
				return (NULL);

			if (pf_get_sport(pd, kif, r, saddr, sxport, daddr,
			    dxport, nsaddr, nsxport, sn
			    ))
			{
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: NAT proxy port allocation "
				    "(%u-%u) failed\n",
				    r->rpool.proxy_port[0],
				    r->rpool.proxy_port[1]));
				return (NULL);
			}
			/*
			 * For NAT64 the destination IPv4 address is derived
			 * from the last 32 bits of synthesized IPv6 address
			 */
			if (r->action == PF_NAT64) {
				ndaddr->v4addr.s_addr = daddr->addr32[3];
				pd->naf = AF_INET;
			}
			break;
		case PF_BINAT:
			switch (direction) {
			case PF_OUT:
				if (r->rpool.cur->addr.type ==
				    PF_ADDR_DYNIFTL) {
					if (r->rpool.cur->addr.p.dyn == NULL)
						return (NULL);
					switch (pd->af) {
#if INET
					case AF_INET:
						if (r->rpool.cur->addr.p.dyn->
						    pfid_acnt4 < 1)
							return (NULL);
						PF_POOLMASK(nsaddr,
						    &r->rpool.cur->addr.p.dyn->
						    pfid_addr4,
						    &r->rpool.cur->addr.p.dyn->
						    pfid_mask4,
						    saddr, AF_INET);
						break;
#endif /* INET */
#if INET6
					case AF_INET6:
						if (r->rpool.cur->addr.p.dyn->
						    pfid_acnt6 < 1)
							return (NULL);
						PF_POOLMASK(nsaddr,
						    &r->rpool.cur->addr.p.dyn->
						    pfid_addr6,
						    &r->rpool.cur->addr.p.dyn->
						    pfid_mask6,
						    saddr, AF_INET6);
						break;
#endif /* INET6 */
					}
				} else {
					PF_POOLMASK(nsaddr,
					    &r->rpool.cur->addr.v.a.addr,
					    &r->rpool.cur->addr.v.a.mask,
					    saddr, pd->af);
				}
				break;
			case PF_IN:
				if (r->src.addr.type == PF_ADDR_DYNIFTL) {
					if (r->src.addr.p.dyn == NULL)
						return (NULL);
					switch (pd->af) {
#if INET
					case AF_INET:
						if (r->src.addr.p.dyn->
						    pfid_acnt4 < 1)
							return (NULL);
						PF_POOLMASK(ndaddr,
						    &r->src.addr.p.dyn->
						    pfid_addr4,
						    &r->src.addr.p.dyn->
						    pfid_mask4,
						    daddr, AF_INET);
						break;
#endif /* INET */
#if INET6
					case AF_INET6:
						if (r->src.addr.p.dyn->
						    pfid_acnt6 < 1)
							return (NULL);
						PF_POOLMASK(ndaddr,
						    &r->src.addr.p.dyn->
						    pfid_addr6,
						    &r->src.addr.p.dyn->
						    pfid_mask6,
						    daddr, AF_INET6);
						break;
#endif /* INET6 */
					}
				} else
					PF_POOLMASK(ndaddr,
					    &r->src.addr.v.a.addr,
					    &r->src.addr.v.a.mask, daddr,
					    pd->af);
				break;
			}
			break;
		case PF_RDR: {
			switch (direction) {
			case PF_OUT:
				if (r->dst.addr.type == PF_ADDR_DYNIFTL) {
					if (r->dst.addr.p.dyn == NULL)
						return (NULL);
					switch (pd->af) {
#if INET
					case AF_INET:
						if (r->dst.addr.p.dyn->
						    pfid_acnt4 < 1)
							return (NULL);
						PF_POOLMASK(nsaddr,
						    &r->dst.addr.p.dyn->
						    pfid_addr4,
						    &r->dst.addr.p.dyn->
						    pfid_mask4,
						    daddr, AF_INET);
						break;
#endif /* INET */
#if INET6
					case AF_INET6:
						if (r->dst.addr.p.dyn->
						    pfid_acnt6 < 1)
							return (NULL);
						PF_POOLMASK(nsaddr,
						    &r->dst.addr.p.dyn->
						    pfid_addr6,
						    &r->dst.addr.p.dyn->
						    pfid_mask6,
						    daddr, AF_INET6);
						break;
#endif /* INET6 */
					}
				} else {
					PF_POOLMASK(nsaddr,
					    &r->dst.addr.v.a.addr,
					    &r->dst.addr.v.a.mask,
					    daddr, pd->af);
				}
				if (nsxport && r->dst.xport.range.port[0])
					nsxport->port =
					    r->dst.xport.range.port[0];
				break;
			case PF_IN:
				if (pf_map_addr(pd->af, r, saddr,
				    ndaddr, NULL, sn))
					return (NULL);
				if ((r->rpool.opts & PF_POOL_TYPEMASK) ==
				    PF_POOL_BITMASK)
					PF_POOLMASK(ndaddr, ndaddr,
					    &r->rpool.cur->addr.v.a.mask, daddr,
					    pd->af);

				if (nsxport && dxport) {
					if (r->rpool.proxy_port[1]) {
						u_int32_t	tmp_nport;

						tmp_nport =
						    ((ntohs(dxport->port) -
						    ntohs(r->dst.xport.range.
						    port[0])) %
						    (r->rpool.proxy_port[1] -
						    r->rpool.proxy_port[0] +
						    1)) + r->rpool.proxy_port[0];

						/* wrap around if necessary */
						if (tmp_nport > 65535)
							tmp_nport -= 65535;
						nsxport->port =
						    htons((u_int16_t)tmp_nport);
					} else if (r->rpool.proxy_port[0]) {
						nsxport->port = htons(r->rpool.
						    proxy_port[0]);
					}
				}
				break;
			}
			break;
		}
		default:
			return (NULL);
		}
	}

	return (r);
}