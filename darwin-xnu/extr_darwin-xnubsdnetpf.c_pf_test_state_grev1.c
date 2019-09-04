#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct pfi_kif {int dummy; } ;
struct pf_state_peer {scalar_t__ state; } ;
struct TYPE_25__ {int /*<<< orphan*/  call_id; } ;
struct TYPE_26__ {TYPE_6__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_24__ {int /*<<< orphan*/  addr; } ;
struct TYPE_22__ {int /*<<< orphan*/  call_id; } ;
struct TYPE_23__ {TYPE_3__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_21__ {int /*<<< orphan*/  addr; } ;
struct pf_state_key_cmp {int af_gwy; int af_lan; TYPE_7__ ext_lan; TYPE_5__ lan; TYPE_4__ gwy; TYPE_2__ ext_gwy; int /*<<< orphan*/  proto_variant; int /*<<< orphan*/  proto; scalar_t__ app_state; } ;
struct pf_state {scalar_t__ timeout; TYPE_14__* state_key; void* expire; struct pf_state_peer src; struct pf_state_peer dst; } ;
struct TYPE_20__ {struct pf_grev1_hdr* grev1; } ;
struct pf_pdesc {int af; int /*<<< orphan*/  mp; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ hdr; } ;
struct pf_grev1_hdr {int /*<<< orphan*/  call_id; } ;
struct TYPE_28__ {TYPE_8__* pptp_state; } ;
struct TYPE_27__ {void* expire; } ;
struct TYPE_17__ {int /*<<< orphan*/  call_id; } ;
struct TYPE_18__ {TYPE_12__ xport; } ;
struct TYPE_19__ {int direction; TYPE_13__ lan; TYPE_11__* app_state; } ;
struct TYPE_15__ {TYPE_9__ grev1; } ;
struct TYPE_16__ {TYPE_10__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_GRE ; 
 void* PFGRE1S_ESTABLISHED ; 
 scalar_t__ PFGRE1S_INITIATING ; 
 scalar_t__ PFTM_GREv1_ESTABLISHED ; 
 scalar_t__ PFTM_GREv1_INITIATING ; 
 scalar_t__ PFTM_TCP_ESTABLISHED ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PF_DROP ; 
 int /*<<< orphan*/  PF_GRE_PPTP_VARIANT ; 
 int PF_IN ; 
 int PF_OUT ; 
 int PF_PASS ; 
 scalar_t__ STATE_GRE_TRANSLATE (TYPE_14__*) ; 
 int /*<<< orphan*/  STATE_LOOKUP () ; 
 int /*<<< orphan*/  pbuf_copy_back (int /*<<< orphan*/ ,int,int,struct pf_grev1_hdr*) ; 
 int /*<<< orphan*/ * pf_lazy_makewritable (struct pf_pdesc*,int /*<<< orphan*/ ,int) ; 
 void* pf_time_second () ; 

__attribute__((used)) static int
pf_test_state_grev1(struct pf_state **state, int direction,
    struct pfi_kif *kif, int off, struct pf_pdesc *pd)
{
	struct pf_state_peer *src;
	struct pf_state_peer *dst;
	struct pf_state_key_cmp key;
	struct pf_grev1_hdr *grev1 = pd->hdr.grev1;

	key.app_state = 0;
	key.proto = IPPROTO_GRE;
	key.proto_variant = PF_GRE_PPTP_VARIANT;
	if (direction == PF_IN)	{
		key.af_gwy = pd->af;
		PF_ACPY(&key.ext_gwy.addr, pd->src, key.af_gwy);
		PF_ACPY(&key.gwy.addr, pd->dst, key.af_gwy);
		key.gwy.xport.call_id = grev1->call_id;
	} else {
		key.af_lan = pd->af;
		PF_ACPY(&key.lan.addr, pd->src, key.af_lan);
		PF_ACPY(&key.ext_lan.addr, pd->dst, key.af_lan);
		key.ext_lan.xport.call_id = grev1->call_id;
	}

	STATE_LOOKUP();

	if (direction == (*state)->state_key->direction) {
		src = &(*state)->src;
		dst = &(*state)->dst;
	} else {
		src = &(*state)->dst;
		dst = &(*state)->src;
	}

	/* update states */
	if (src->state < PFGRE1S_INITIATING)
		src->state = PFGRE1S_INITIATING;

	/* update expire time */
	(*state)->expire = pf_time_second();
	if (src->state >= PFGRE1S_INITIATING &&
	    dst->state >= PFGRE1S_INITIATING) {
		if ((*state)->timeout != PFTM_TCP_ESTABLISHED)
			(*state)->timeout = PFTM_GREv1_ESTABLISHED;
		src->state = PFGRE1S_ESTABLISHED;
		dst->state = PFGRE1S_ESTABLISHED;
	} else {
		(*state)->timeout = PFTM_GREv1_INITIATING;
	}

	if ((*state)->state_key->app_state)
		(*state)->state_key->app_state->u.grev1.pptp_state->expire =
		    pf_time_second();

	/* translate source/destination address, if necessary */
	if (STATE_GRE_TRANSLATE((*state)->state_key)) {
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
			grev1->call_id = (*state)->state_key->lan.xport.call_id;

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

		if (pf_lazy_makewritable(pd, pd->mp, off + sizeof (*grev1)) ==
		    NULL)
			return (PF_DROP);
		pbuf_copy_back(pd->mp, off, sizeof (*grev1), grev1);
	}

	return (PF_PASS);
}