#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct il_tx_queue {int dummy; } ;
struct il_priv {scalar_t__ txq; TYPE_1__* cfg; } ;
struct TYPE_2__ {int num_of_queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

int
il_alloc_txq_mem(struct il_priv *il)
{
	if (!il->txq)
		il->txq =
		    kzalloc(sizeof(struct il_tx_queue) *
			    il->cfg->num_of_queues, GFP_KERNEL);
	if (!il->txq) {
		IL_ERR("Not enough memory for txq\n");
		return -ENOMEM;
	}
	return 0;
}