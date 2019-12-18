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
struct bna_rxf {int /*<<< orphan*/  rx; int /*<<< orphan*/  start_cbarg; int /*<<< orphan*/  start_cbfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXF_E_START ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rx_cb_rxf_started ; 

__attribute__((used)) static void
bna_rxf_start(struct bna_rxf *rxf)
{
	rxf->start_cbfn = bna_rx_cb_rxf_started;
	rxf->start_cbarg = rxf->rx;
	bfa_fsm_send_event(rxf, RXF_E_START);
}