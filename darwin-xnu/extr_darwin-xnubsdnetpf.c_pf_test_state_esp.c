#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct pfi_kif {int dummy; } ;
struct pf_state_peer {scalar_t__ state; } ;
struct TYPE_14__ {scalar_t__ spi; } ;
struct TYPE_15__ {TYPE_10__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_21__ {scalar_t__ spi; } ;
struct TYPE_22__ {TYPE_4__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_20__ {int /*<<< orphan*/  addr; } ;
struct TYPE_19__ {int /*<<< orphan*/  addr; } ;
struct pf_state_key_cmp {int af_gwy; int af_lan; TYPE_11__ ext_lan; TYPE_5__ gwy; TYPE_3__ lan; TYPE_2__ ext_gwy; int /*<<< orphan*/  proto; } ;
struct TYPE_16__ {scalar_t__ spi; } ;
struct TYPE_17__ {TYPE_12__ xport; } ;
struct TYPE_25__ {scalar_t__ spi; } ;
struct TYPE_26__ {TYPE_8__ xport; } ;
struct TYPE_23__ {scalar_t__ spi; } ;
struct TYPE_24__ {TYPE_6__ xport; } ;
struct pf_state_key {scalar_t__ flowhash; int direction; int /*<<< orphan*/  flowsrc; TYPE_13__ ext_lan; TYPE_9__ gwy; TYPE_7__ lan; } ;
struct pf_state {struct pf_state_key* state_key; int /*<<< orphan*/  timeout; int /*<<< orphan*/  expire; struct pf_state_peer src; struct pf_state_peer dst; int /*<<< orphan*/  unlink_hooks; } ;
struct TYPE_18__ {struct pf_esp_hdr* esp; } ;
struct pf_pdesc {int af; int pktflags; scalar_t__ flowhash; int /*<<< orphan*/  flowsrc; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ hdr; } ;
struct pf_esp_hdr {scalar_t__ spi; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int HOOK_FREE ; 
 int HOOK_REMOVE ; 
 int /*<<< orphan*/  IPPROTO_ESP ; 
 void* PFESPS_ESTABLISHED ; 
 scalar_t__ PFESPS_INITIATING ; 
 int /*<<< orphan*/  PFTM_ESP_ESTABLISHED ; 
 int /*<<< orphan*/  PFTM_ESP_INITIATING ; 
 int /*<<< orphan*/  PFTM_UNLINKED ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PF_DROP ; 
 int /*<<< orphan*/  PF_DT_SKIP_EXTGWY ; 
 int /*<<< orphan*/  PF_DT_SKIP_LANEXT ; 
 int PF_IN ; 
 int PF_OUT ; 
 int PF_PASS ; 
 int PKTF_FLOW_ADV ; 
 int PKTF_FLOW_ID ; 
 scalar_t__ RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_state_key*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_state_key*) ; 
 scalar_t__ STATE_ADDR_TRANSLATE (struct pf_state_key*) ; 
 int /*<<< orphan*/  hook_runloop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct pf_state_key_cmp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pf_detach_state (struct pf_state*,int /*<<< orphan*/ ) ; 
 struct pf_state* pf_find_state (struct pfi_kif*,struct pf_state_key_cmp*,int) ; 
 int /*<<< orphan*/  pf_free_state (struct pf_state*) ; 
 int /*<<< orphan*/  pf_src_tree_remove_state (struct pf_state*) ; 
 scalar_t__ pf_state_lookup_aux (struct pf_state**,struct pfi_kif*,int,int*) ; 
 int /*<<< orphan*/  pf_state_tree_ext_gwy ; 
 int /*<<< orphan*/  pf_state_tree_lan_ext ; 
 int /*<<< orphan*/  pf_statetbl_ext_gwy ; 
 int /*<<< orphan*/  pf_statetbl_lan_ext ; 
 int /*<<< orphan*/  pf_time_second () ; 

__attribute__((used)) static int
pf_test_state_esp(struct pf_state **state, int direction, struct pfi_kif *kif,
    int off, struct pf_pdesc *pd)
{
#pragma unused(off)
	struct pf_state_peer *src;
	struct pf_state_peer *dst;
	struct pf_state_key_cmp key;
	struct pf_esp_hdr *esp = pd->hdr.esp;
	int action;

	memset(&key, 0, sizeof (key));
	key.proto = IPPROTO_ESP;
	if (direction == PF_IN)	{
		key.af_gwy = pd->af;
		PF_ACPY(&key.ext_gwy.addr, pd->src, key.af_gwy);
		PF_ACPY(&key.gwy.addr, pd->dst, key.af_gwy);
		key.gwy.xport.spi = esp->spi;
	} else {
		key.af_lan = pd->af;
		PF_ACPY(&key.lan.addr, pd->src, key.af_lan);
		PF_ACPY(&key.ext_lan.addr, pd->dst, key.af_lan);
		key.ext_lan.xport.spi = esp->spi;
	}

	*state = pf_find_state(kif, &key, direction);

	if (*state == 0) {
		struct pf_state *s;

		/*
		 * <jhw@apple.com>
		 * No matching state.  Look for a blocking state.  If we find
		 * one, then use that state and move it so that it's keyed to
		 * the SPI in the current packet.
		 */
		if (direction == PF_IN) {
			key.gwy.xport.spi = 0;

			s = pf_find_state(kif, &key, direction);
			if (s) {
				struct pf_state_key *sk = s->state_key;

				RB_REMOVE(pf_state_tree_ext_gwy,
				    &pf_statetbl_ext_gwy, sk);
				sk->lan.xport.spi = sk->gwy.xport.spi =
				    esp->spi;

				if (RB_INSERT(pf_state_tree_ext_gwy,
				    &pf_statetbl_ext_gwy, sk))
					pf_detach_state(s, PF_DT_SKIP_EXTGWY);
				else
					*state = s;
			}
		} else {
			key.ext_lan.xport.spi = 0;

			s = pf_find_state(kif, &key, direction);
			if (s) {
				struct pf_state_key *sk = s->state_key;

				RB_REMOVE(pf_state_tree_lan_ext,
				    &pf_statetbl_lan_ext, sk);
				sk->ext_lan.xport.spi = esp->spi;

				if (RB_INSERT(pf_state_tree_lan_ext,
				    &pf_statetbl_lan_ext, sk))
					pf_detach_state(s, PF_DT_SKIP_LANEXT);
				else
					*state = s;
			}
		}

		if (s) {
			if (*state == 0) {
#if NPFSYNC
				if (s->creatorid == pf_status.hostid)
					pfsync_delete_state(s);
#endif
				s->timeout = PFTM_UNLINKED;
				hook_runloop(&s->unlink_hooks,
				    HOOK_REMOVE|HOOK_FREE);
				pf_src_tree_remove_state(s);
				pf_free_state(s);
				return (PF_DROP);
			}
		}
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

	if (direction == (*state)->state_key->direction) {
		src = &(*state)->src;
		dst = &(*state)->dst;
	} else {
		src = &(*state)->dst;
		dst = &(*state)->src;
	}

	/* update states */
	if (src->state < PFESPS_INITIATING)
		src->state = PFESPS_INITIATING;

	/* update expire time */
	(*state)->expire = pf_time_second();
	if (src->state >= PFESPS_INITIATING &&
	    dst->state >= PFESPS_INITIATING) {
		(*state)->timeout = PFTM_ESP_ESTABLISHED;
		src->state = PFESPS_ESTABLISHED;
		dst->state = PFESPS_ESTABLISHED;
	} else {
		(*state)->timeout = PFTM_ESP_INITIATING;
	}
	/* translate source/destination address, if necessary */
	if (STATE_ADDR_TRANSLATE((*state)->state_key)) {
		if (direction == PF_OUT) {
			switch (pd->af) {
#if INET
			case AF_INET:
				pf_change_a(&pd->src->v4addr.s_addr,
				    pd->ip_sum,
				    (*state)->state_key->gwy.addr.v4addr.s_addr, 0);
				break;
#endif /* INET */
#if INET6
			case AF_INET6:
				PF_ACPY(pd->src, &(*state)->state_key->gwy.addr,
				    pd->af);
				break;
#endif /* INET6 */
			}
		} else {
			switch (pd->af) {
#if INET
			case AF_INET:
				pf_change_a(&pd->dst->v4addr.s_addr,
				    pd->ip_sum,
				    (*state)->state_key->lan.addr.v4addr.s_addr, 0);
				break;
#endif /* INET */
#if INET6
			case AF_INET6:
				PF_ACPY(pd->dst, &(*state)->state_key->lan.addr,
				    pd->af);
				break;
#endif /* INET6 */
			}
		}
	}

	return (PF_PASS);
}