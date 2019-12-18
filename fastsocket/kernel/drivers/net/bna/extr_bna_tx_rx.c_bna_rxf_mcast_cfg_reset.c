#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct bna_rxf {int /*<<< orphan*/  mcast_pending_add_q; int /*<<< orphan*/  mcast_active_q; TYPE_2__* rx; int /*<<< orphan*/  mcast_pending_del_q; } ;
struct bna_mac {int dummy; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_4__ {TYPE_1__* bna; } ;
struct TYPE_3__ {int /*<<< orphan*/  mcam_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_qe_init (struct list_head*) ; 
 int /*<<< orphan*/  bna_mcam_mod_mac_put (int /*<<< orphan*/ *,struct bna_mac*) ; 
 int bna_rxf_mcast_del (struct bna_rxf*,struct bna_mac*,int) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bna_rxf_mcast_cfg_reset(struct bna_rxf *rxf, enum bna_cleanup_type cleanup)
{
	struct list_head *qe;
	struct bna_mac *mac;
	int ret;

	/* Throw away delete pending mcast entries */
	while (!list_empty(&rxf->mcast_pending_del_q)) {
		bfa_q_deq(&rxf->mcast_pending_del_q, &qe);
		bfa_q_qe_init(qe);
		mac = (struct bna_mac *)qe;
		ret = bna_rxf_mcast_del(rxf, mac, cleanup);
		bna_mcam_mod_mac_put(&rxf->rx->bna->mcam_mod, mac);
		if (ret)
			return ret;
	}

	/* Move active mcast entries to pending_add_q */
	while (!list_empty(&rxf->mcast_active_q)) {
		bfa_q_deq(&rxf->mcast_active_q, &qe);
		bfa_q_qe_init(qe);
		list_add_tail(qe, &rxf->mcast_pending_add_q);
		mac = (struct bna_mac *)qe;
		if (bna_rxf_mcast_del(rxf, mac, cleanup))
			return 1;
	}

	return 0;
}