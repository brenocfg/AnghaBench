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
struct bna_ethport {int flags; int /*<<< orphan*/ * adminup_cbfn; int /*<<< orphan*/ * stop_cbfn; scalar_t__ rx_started_count; int /*<<< orphan*/  link_cbfn; int /*<<< orphan*/  link_status; struct bna* bna; } ;
struct bna {int dummy; } ;

/* Variables and functions */
 int BNA_ETHPORT_F_ADMIN_UP ; 
 int BNA_ETHPORT_F_PORT_ENABLED ; 
 int /*<<< orphan*/  BNA_LINK_DOWN ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ethport_sm_stopped ; 
 int /*<<< orphan*/  bnad_cb_ethport_link_status ; 

__attribute__((used)) static void
bna_ethport_init(struct bna_ethport *ethport, struct bna *bna)
{
	ethport->flags |= (BNA_ETHPORT_F_ADMIN_UP | BNA_ETHPORT_F_PORT_ENABLED);
	ethport->bna = bna;

	ethport->link_status = BNA_LINK_DOWN;
	ethport->link_cbfn = bnad_cb_ethport_link_status;

	ethport->rx_started_count = 0;

	ethport->stop_cbfn = NULL;
	ethport->adminup_cbfn = NULL;

	bfa_fsm_set_state(ethport, bna_ethport_sm_stopped);
}