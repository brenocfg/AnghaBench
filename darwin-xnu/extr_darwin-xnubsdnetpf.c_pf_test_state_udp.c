#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_21__ ;
typedef  struct TYPE_39__   TYPE_20__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_19__ ;
typedef  struct TYPE_36__   TYPE_18__ ;
typedef  struct TYPE_35__   TYPE_17__ ;
typedef  struct TYPE_34__   TYPE_16__ ;
typedef  struct TYPE_33__   TYPE_15__ ;
typedef  struct TYPE_32__   TYPE_14__ ;
typedef  struct TYPE_31__   TYPE_13__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct udphdr {int /*<<< orphan*/  uh_sum; int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; scalar_t__ uh_ulen; } ;
struct pfi_kif {int dummy; } ;
struct pf_state_peer {scalar_t__ state; } ;
struct TYPE_30__ {int /*<<< orphan*/  port; } ;
struct TYPE_31__ {int /*<<< orphan*/  addr; TYPE_12__ xport; } ;
struct TYPE_48__ {int /*<<< orphan*/  port; } ;
struct TYPE_28__ {int /*<<< orphan*/  addr; TYPE_9__ xport; } ;
struct TYPE_43__ {int /*<<< orphan*/  port; } ;
struct TYPE_44__ {TYPE_4__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_41__ {int /*<<< orphan*/  port; } ;
struct TYPE_42__ {TYPE_2__ xport; int /*<<< orphan*/  addr; } ;
struct pf_state_key_cmp {int proto_variant; scalar_t__ af_lan; scalar_t__ af_gwy; TYPE_13__ ext_gwy; TYPE_10__ ext_lan; struct pf_app_state* app_state; TYPE_5__ lan; TYPE_3__ gwy; int /*<<< orphan*/  proto; } ;
struct TYPE_37__ {int /*<<< orphan*/  port; } ;
struct TYPE_39__ {TYPE_19__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_35__ {int /*<<< orphan*/  port; } ;
struct TYPE_36__ {TYPE_17__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_29__ {int /*<<< orphan*/  port; } ;
struct TYPE_34__ {int /*<<< orphan*/  addr; TYPE_11__ xport; } ;
struct TYPE_47__ {int /*<<< orphan*/  port; } ;
struct TYPE_33__ {int /*<<< orphan*/  addr; TYPE_8__ xport; } ;
struct pf_state_key {scalar_t__ flowhash; int direction; scalar_t__ af_lan; int proto_variant; scalar_t__ af_gwy; TYPE_20__ lan; TYPE_18__ gwy; TYPE_16__ ext_gwy; TYPE_15__ ext_lan; TYPE_14__* app_state; int /*<<< orphan*/  flowsrc; } ;
struct pf_state {int /*<<< orphan*/  timeout; int /*<<< orphan*/  expire; struct pf_state_peer src; struct pf_state_peer dst; struct pf_state_key* state_key; } ;
struct TYPE_38__ {struct udphdr* udp; } ;
struct pf_pdesc {scalar_t__ af; int pktflags; scalar_t__ flowhash; scalar_t__ lmw; scalar_t__ naf; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/ * dst; TYPE_21__* mp; int /*<<< orphan*/ * src; int /*<<< orphan*/  flowsrc; TYPE_1__ hdr; } ;
struct pf_ike_hdr {scalar_t__ initiator_cookie; } ;
struct TYPE_45__ {scalar_t__ cookie; } ;
struct TYPE_46__ {TYPE_6__ ike; } ;
struct pf_app_state {TYPE_7__ u; void* compare_ext_gwy; void* compare_lan_ext; } ;
struct TYPE_40__ {int pb_packet_len; } ;
typedef  TYPE_21__ pbuf_t ;
typedef  int /*<<< orphan*/  ike ;
struct TYPE_32__ {int /*<<< orphan*/  (* handler ) (struct pf_state*,int,scalar_t__,struct pf_pdesc*,struct pfi_kif*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPFPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PFRES_MEMORY ; 
 int /*<<< orphan*/  PFTM_UDP_MULTIPLE ; 
 int /*<<< orphan*/  PFTM_UDP_SINGLE ; 
 scalar_t__ PFUDPS_MULTIPLE ; 
 scalar_t__ PFUDPS_SINGLE ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int PF_DROP ; 
 int PF_EXTFILTER_AD ; 
 int PF_EXTFILTER_APD ; 
 int PF_EXTFILTER_EI ; 
 size_t PF_IKE_PACKET_MINSIZE ; 
 scalar_t__ PF_IKE_PORT ; 
 int PF_OUT ; 
 int PF_PASS ; 
 int PKTF_FLOW_ADV ; 
 int PKTF_FLOW_ID ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_TRANSLATE (struct pf_state_key*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_copy_back (TYPE_21__*,int,int,struct udphdr*) ; 
 int /*<<< orphan*/  pbuf_copy_data (TYPE_21__*,int,size_t,struct pf_ike_hdr*) ; 
 int /*<<< orphan*/  pf_change_ap (int,TYPE_21__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int) ; 
 int pf_do_nat64 (struct pf_state_key*,struct pf_pdesc*,TYPE_21__*,int) ; 
 struct pf_state* pf_find_state (struct pfi_kif*,struct pf_state_key_cmp*,int) ; 
 void* pf_ike_compare ; 
 int /*<<< orphan*/ * pf_lazy_makewritable (struct pf_pdesc*,TYPE_21__*,int) ; 
 scalar_t__ pf_state_lookup_aux (struct pf_state**,struct pfi_kif*,int,int*) ; 
 int /*<<< orphan*/  pf_time_second () ; 
 int /*<<< orphan*/  stub1 (struct pf_state*,int,scalar_t__,struct pf_pdesc*,struct pfi_kif*) ; 

__attribute__((used)) static int
pf_test_state_udp(struct pf_state **state, int direction, struct pfi_kif *kif,
    pbuf_t *pbuf, int off, void *h, struct pf_pdesc *pd, u_short *reason)
{
#pragma unused(h)
	struct pf_state_peer	*src, *dst;
	struct pf_state_key_cmp	 key;
	struct pf_state_key	*sk;
	struct udphdr		*uh = pd->hdr.udp;
	struct pf_app_state as;
	int action, extfilter;
	key.app_state = 0;
	key.proto_variant = PF_EXTFILTER_APD;

	key.proto = IPPROTO_UDP;
	key.af_lan = key.af_gwy = pd->af;

	/*
	 * For NAT64 the first time rule search and state creation
	 * is done on the incoming side only.
	 * Once the state gets created, NAT64's LAN side (ipv6) will
	 * not be able to find the state in ext-gwy tree as that normally
	 * is intended to be looked up for incoming traffic from the
	 * WAN side.
	 * Therefore to handle NAT64 case we init keys here for both
	 * lan-ext as well as ext-gwy trees.
	 * In the state lookup we attempt a lookup on both trees if
	 * first one does not return any result and return a match if
	 * the match state's was created by NAT64 rule.
	 */
	PF_ACPY(&key.ext_gwy.addr, pd->src, key.af_gwy);
	PF_ACPY(&key.gwy.addr, pd->dst, key.af_gwy);
	key.ext_gwy.xport.port = uh->uh_sport;
	key.gwy.xport.port = uh->uh_dport;

	PF_ACPY(&key.lan.addr, pd->src, key.af_lan);
	PF_ACPY(&key.ext_lan.addr, pd->dst, key.af_lan);
	key.lan.xport.port = uh->uh_sport;
	key.ext_lan.xport.port = uh->uh_dport;

	if (ntohs(uh->uh_sport) == PF_IKE_PORT &&
	    ntohs(uh->uh_dport) == PF_IKE_PORT) {
		struct pf_ike_hdr ike;
		size_t plen = pbuf->pb_packet_len - off - sizeof (*uh);
		if (plen < PF_IKE_PACKET_MINSIZE) {
			DPFPRINTF(PF_DEBUG_MISC,
			    ("pf: IKE message too small.\n"));
			return (PF_DROP);
		}

		if (plen > sizeof (ike))
			plen = sizeof (ike);
		pbuf_copy_data(pbuf, off + sizeof (*uh), plen, &ike);

		if (ike.initiator_cookie) {
			key.app_state = &as;
			as.compare_lan_ext = pf_ike_compare;
			as.compare_ext_gwy = pf_ike_compare;
			as.u.ike.cookie = ike.initiator_cookie;
		} else {
			/*
			 * <http://tools.ietf.org/html/\
			 *    draft-ietf-ipsec-nat-t-ike-01>
			 * Support non-standard NAT-T implementations that
			 * push the ESP packet over the top of the IKE packet.
			 * Do not drop packet.
			 */
			DPFPRINTF(PF_DEBUG_MISC,
			    ("pf: IKE initiator cookie = 0.\n"));
		}
	}

	*state = pf_find_state(kif, &key, direction);

	if (!key.app_state && *state == 0) {
		key.proto_variant = PF_EXTFILTER_AD;
		*state = pf_find_state(kif, &key, direction);
	}

	if (!key.app_state && *state == 0) {
		key.proto_variant = PF_EXTFILTER_EI;
		*state = pf_find_state(kif, &key, direction);
	}

	/* similar to STATE_LOOKUP() */
	if (*state != NULL && pd != NULL && !(pd->pktflags & PKTF_FLOW_ID)) {
		pd->flowsrc = (*state)->state_key->flowsrc;
		pd->flowhash = (*state)->state_key->flowhash;
		if (pd->flowhash != 0) {
			pd->pktflags |= PKTF_FLOW_ID;
			pd->pktflags &= ~PKTF_FLOW_ADV;
		}
	}

	if (pf_state_lookup_aux(state, kif, direction, &action))
		return (action);

	sk = (*state)->state_key;

	/*
	 * In case of NAT64 the translation is first applied on the LAN
	 * side. Therefore for stack's address family comparison
	 * we use sk->af_lan.
	 */
	if ((direction == sk->direction) && (pd->af == sk->af_lan)) {
		src = &(*state)->src;
		dst = &(*state)->dst;
	} else {
		src = &(*state)->dst;
		dst = &(*state)->src;
	}

	/* update states */
	if (src->state < PFUDPS_SINGLE)
		src->state = PFUDPS_SINGLE;
	if (dst->state == PFUDPS_SINGLE)
		dst->state = PFUDPS_MULTIPLE;

	/* update expire time */
	(*state)->expire = pf_time_second();
	if (src->state == PFUDPS_MULTIPLE && dst->state == PFUDPS_MULTIPLE)
		(*state)->timeout = PFTM_UDP_MULTIPLE;
	else
		(*state)->timeout = PFTM_UDP_SINGLE;

	extfilter = sk->proto_variant;
	if (extfilter > PF_EXTFILTER_APD) {
		if (direction == PF_OUT) {
			sk->ext_lan.xport.port = key.ext_lan.xport.port;
			if (extfilter > PF_EXTFILTER_AD)
				PF_ACPY(&sk->ext_lan.addr, &key.ext_lan.addr,
					key.af_lan);
		} else {
			sk->ext_gwy.xport.port = key.ext_gwy.xport.port;
			if (extfilter > PF_EXTFILTER_AD)
				PF_ACPY(&sk->ext_gwy.addr, &key.ext_gwy.addr,
					key.af_gwy);
		}
	}

	if (sk->app_state && sk->app_state->handler) {
		sk->app_state->handler(*state, direction, off + uh->uh_ulen,
					pd, kif);
		if (pd->lmw < 0) {
			REASON_SET(reason, PFRES_MEMORY);
			return (PF_DROP);
		}
		pbuf = pd->mp;	// XXXSCW: Why?
	}

	/* translate source/destination address, if necessary */
	if (STATE_TRANSLATE(sk)) {
		if (pf_lazy_makewritable(pd, pbuf, off + sizeof (*uh)) == NULL) {
			REASON_SET(reason, PFRES_MEMORY);
			return (PF_DROP);
		}

		pd->naf = (pd->af == sk->af_lan) ? sk->af_gwy : sk->af_lan;

		if (direction == PF_OUT) {
			pf_change_ap(direction, pd->mp, pd->src, &uh->uh_sport,
				     pd->ip_sum, &uh->uh_sum, &sk->gwy.addr,
				     sk->gwy.xport.port, 1, pd->af, pd->naf, 1);
		} else {
			if (pd->af != pd->naf) {

				if (pd->af == sk->af_gwy) {
					pf_change_ap(direction, pd->mp, pd->dst,
						&uh->uh_dport, pd->ip_sum,
						&uh->uh_sum, &sk->lan.addr,
						sk->lan.xport.port, 1,
						pd->af, pd->naf, 0);

					pf_change_ap(direction, pd->mp, pd->src,
						&uh->uh_sport, pd->ip_sum,
						&uh->uh_sum, &sk->ext_lan.addr,
						uh->uh_sport, 1, pd->af,
						pd->naf, 0);

				} else {
					pf_change_ap(direction, pd->mp, pd->dst,
						&uh->uh_dport, pd->ip_sum,
						&uh->uh_sum, &sk->ext_gwy.addr,
						uh->uh_dport, 1, pd->af,
						pd->naf, 0);

					pf_change_ap(direction, pd->mp, pd->src,
						&uh->uh_sport, pd->ip_sum,
						&uh->uh_sum, &sk->gwy.addr,
						sk->gwy.xport.port, 1, pd->af,
						pd->naf, 0);
				}
			} else {
				pf_change_ap(direction, pd->mp, pd->dst,
						&uh->uh_dport, pd->ip_sum,
						&uh->uh_sum, &sk->lan.addr,
						sk->lan.xport.port, 1,
						pd->af, pd->naf, 1);
			}
		}

		pbuf_copy_back(pbuf, off, sizeof (*uh), uh);
		if (sk->af_lan != sk->af_gwy)
			return (pf_do_nat64(sk, pd, pbuf, off));
	}
	return (PF_PASS);
}