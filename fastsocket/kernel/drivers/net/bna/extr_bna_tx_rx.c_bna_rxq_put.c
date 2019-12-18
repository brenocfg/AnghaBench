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
struct bna_rxq {int /*<<< orphan*/  qe; } ;
struct bna_rx_mod {int /*<<< orphan*/  rxq_free_count; int /*<<< orphan*/  rxq_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bna_rxq_put(struct bna_rx_mod *rx_mod, struct bna_rxq *rxq)
{
	bfa_q_qe_init(&rxq->qe);
	list_add_tail(&rxq->qe, &rx_mod->rxq_free_q);
	rx_mod->rxq_free_count++;
}