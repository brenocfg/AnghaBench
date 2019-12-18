#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int port; int call_id; int spi; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; TYPE_2__ xport; } ;
struct TYPE_7__ {int port; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; TYPE_1__ xport; } ;
struct pf_state_key {int proto; int af_lan; int proto_variant; TYPE_5__* app_state; TYPE_4__ ext_lan; TYPE_3__ lan; } ;
struct TYPE_11__ {int (* compare_lan_ext ) (TYPE_5__*,TYPE_5__*) ;} ;

/* Variables and functions */
#define  AF_INET 135 
#define  AF_INET6 134 
#define  IPPROTO_ESP 133 
#define  IPPROTO_GRE 132 
#define  IPPROTO_ICMP 131 
#define  IPPROTO_ICMPV6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  PF_AZERO (int /*<<< orphan*/ *,int const) ; 
 int PF_EXTFILTER_AD ; 
 int PF_EXTFILTER_APD ; 
 int PF_EXTFILTER_EI ; 
 int PF_GRE_PPTP_VARIANT ; 
 int pf_addr_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_5__*,TYPE_5__*) ; 

__attribute__((used)) static __inline int
pf_state_compare_lan_ext(struct pf_state_key *a, struct pf_state_key *b)
{
	int	diff;
	int	extfilter;

	if ((diff = a->proto - b->proto) != 0)
		return (diff);
	if ((diff = a->af_lan - b->af_lan) != 0)
		return (diff);

	extfilter = PF_EXTFILTER_APD;

	switch (a->proto) {
	case IPPROTO_ICMP:
	case IPPROTO_ICMPV6:
		if ((diff = a->lan.xport.port - b->lan.xport.port) != 0)
			return (diff);
		break;

	case IPPROTO_TCP:
		if ((diff = a->lan.xport.port - b->lan.xport.port) != 0)
			return (diff);
		if ((diff = a->ext_lan.xport.port - b->ext_lan.xport.port) != 0)
			return (diff);
		break;

	case IPPROTO_UDP:
		if ((diff = a->proto_variant - b->proto_variant))
			return (diff);
		extfilter = a->proto_variant;
		if ((diff = a->lan.xport.port - b->lan.xport.port) != 0)
			return (diff);
		if ((extfilter < PF_EXTFILTER_AD) &&
		    (diff = a->ext_lan.xport.port - b->ext_lan.xport.port) != 0)
			return (diff);
		break;

	case IPPROTO_GRE:
		if (a->proto_variant == PF_GRE_PPTP_VARIANT &&
		    a->proto_variant == b->proto_variant) {
			if (!!(diff = a->ext_lan.xport.call_id -
			    b->ext_lan.xport.call_id))
				return (diff);
		}
		break;

	case IPPROTO_ESP:
		if (!!(diff = a->ext_lan.xport.spi - b->ext_lan.xport.spi))
			return (diff);
		break;

	default:
		break;
	}

	switch (a->af_lan) {
#if INET
	case AF_INET:
		if ((diff = pf_addr_compare(&a->lan.addr, &b->lan.addr,
					    a->af_lan)) != 0)
			return (diff);

		if (extfilter < PF_EXTFILTER_EI) {
			if ((diff = pf_addr_compare(&a->ext_lan.addr,
						    &b->ext_lan.addr,
						    a->af_lan)) != 0)
				return (diff);
		}
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		if ((diff = pf_addr_compare(&a->lan.addr, &b->lan.addr,
					    a->af_lan)) != 0)
			return (diff);

		if (extfilter < PF_EXTFILTER_EI ||
		    !PF_AZERO(&b->ext_lan.addr, AF_INET6)) {
			if ((diff = pf_addr_compare(&a->ext_lan.addr,
						    &b->ext_lan.addr,
						    a->af_lan)) != 0)
				return (diff);
		}
		break;
#endif /* INET6 */
	}

	if (a->app_state && b->app_state) {
		if (a->app_state->compare_lan_ext &&
		    b->app_state->compare_lan_ext) {
			diff = (const char *)b->app_state->compare_lan_ext -
			    (const char *)a->app_state->compare_lan_ext;
			if (diff != 0)
				return (diff);
			diff = a->app_state->compare_lan_ext(a->app_state,
			    b->app_state);
			if (diff != 0)
				return (diff);
		}
	}

	return (0);
}