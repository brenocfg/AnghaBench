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
struct list_head {int dummy; } ;
struct bna_rxp {int /*<<< orphan*/  qe; } ;
struct bna_rx_mod {int /*<<< orphan*/  rxp_free_count; int /*<<< orphan*/  rxp_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bna_rxp *
bna_rxp_get(struct bna_rx_mod *rx_mod)
{
	struct list_head	*qe = NULL;
	struct bna_rxp *rxp = NULL;

	bfa_q_deq(&rx_mod->rxp_free_q, &qe);
	rx_mod->rxp_free_count--;
	rxp = (struct bna_rxp *)qe;
	bfa_q_qe_init(&rxp->qe);

	return rxp;
}