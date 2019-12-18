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
struct bna_rxf {TYPE_2__* rx; } ;
struct bna_mcam_handle {scalar_t__ refcnt; int /*<<< orphan*/  qe; int /*<<< orphan*/  handle; } ;
struct bna_mac {struct bna_mcam_handle* handle; } ;
typedef  enum bna_cleanup_type { ____Placeholder_bna_cleanup_type } bna_cleanup_type ;
struct TYPE_4__ {TYPE_1__* bna; } ;
struct TYPE_3__ {int /*<<< orphan*/  mcam_mod; } ;

/* Variables and functions */
 int BNA_HARD_CLEANUP ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_bfi_mcast_del_req (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_mcam_mod_handle_put (int /*<<< orphan*/ *,struct bna_mcam_handle*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bna_rxf_mcast_del(struct bna_rxf *rxf, struct bna_mac *mac,
		enum bna_cleanup_type cleanup)
{
	struct bna_mcam_handle *mchandle;
	int ret = 0;

	mchandle = mac->handle;
	if (mchandle == NULL)
		return ret;

	mchandle->refcnt--;
	if (mchandle->refcnt == 0) {
		if (cleanup == BNA_HARD_CLEANUP) {
			bna_bfi_mcast_del_req(rxf, mchandle->handle);
			ret = 1;
		}
		list_del(&mchandle->qe);
		bfa_q_qe_init(&mchandle->qe);
		bna_mcam_mod_handle_put(&rxf->rx->bna->mcam_mod, mchandle);
	}
	mac->handle = NULL;

	return ret;
}