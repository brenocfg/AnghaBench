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
struct TYPE_3__ {int mtu_comp_status; int /*<<< orphan*/  mtu_comp; } ;
struct TYPE_4__ {int /*<<< orphan*/  enet; } ;
struct bnad {TYPE_1__ bnad_completions; int /*<<< orphan*/  bna_lock; TYPE_2__ bna; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_enet_mtu_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_cb_enet_mtu_set ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnad_mtu_set(struct bnad *bnad, int mtu)
{
	unsigned long flags;

	init_completion(&bnad->bnad_completions.mtu_comp);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_mtu_set(&bnad->bna.enet, mtu, bnad_cb_enet_mtu_set);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	wait_for_completion(&bnad->bnad_completions.mtu_comp);

	return bnad->bnad_completions.mtu_comp_status;
}