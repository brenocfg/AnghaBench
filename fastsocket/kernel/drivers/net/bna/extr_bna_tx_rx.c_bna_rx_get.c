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
struct bna_rx_mod {int /*<<< orphan*/  rx_active_q; int /*<<< orphan*/  rx_free_count; int /*<<< orphan*/  rx_free_q; } ;
struct bna_rx {int type; int /*<<< orphan*/  qe; } ;
typedef  enum bna_rx_type { ____Placeholder_bna_rx_type } bna_rx_type ;

/* Variables and functions */
 int BNA_RX_T_REGULAR ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_deq_tail (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  bfa_q_qe_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bna_rx *
bna_rx_get(struct bna_rx_mod *rx_mod, enum bna_rx_type type)
{
	struct list_head	*qe = NULL;
	struct bna_rx *rx = NULL;

	if (type == BNA_RX_T_REGULAR) {
		bfa_q_deq(&rx_mod->rx_free_q, &qe);
	} else
		bfa_q_deq_tail(&rx_mod->rx_free_q, &qe);

	rx_mod->rx_free_count--;
	rx = (struct bna_rx *)qe;
	bfa_q_qe_init(&rx->qe);
	list_add_tail(&rx->qe, &rx_mod->rx_active_q);
	rx->type = type;

	return rx;
}