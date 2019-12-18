#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bnad_tx_info {TYPE_3__** tcb; } ;
struct bnad {TYPE_2__* msix_table; TYPE_1__* netdev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_6__ {int intr_vector; int id; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 scalar_t__ bnad_msix_tx ; 
 int /*<<< orphan*/  bnad_tx_msix_unregister (struct bnad*,struct bnad_tx_info*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
bnad_tx_msix_register(struct bnad *bnad, struct bnad_tx_info *tx_info,
			u32 tx_id, int num_txqs)
{
	int i;
	int err;
	int vector_num;

	for (i = 0; i < num_txqs; i++) {
		vector_num = tx_info->tcb[i]->intr_vector;
		sprintf(tx_info->tcb[i]->name, "%s TXQ %d", bnad->netdev->name,
				tx_id + tx_info->tcb[i]->id);
		err = request_irq(bnad->msix_table[vector_num].vector,
				  (irq_handler_t)bnad_msix_tx, 0,
				  tx_info->tcb[i]->name,
				  tx_info->tcb[i]);
		if (err)
			goto err_return;
	}

	return 0;

err_return:
	if (i > 0)
		bnad_tx_msix_unregister(bnad, tx_info, (i - 1));
	return -1;
}