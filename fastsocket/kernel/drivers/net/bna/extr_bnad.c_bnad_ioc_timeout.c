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
struct TYPE_3__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_4__ {TYPE_1__ ioceth; } ;
struct bnad {int /*<<< orphan*/  bna_lock; TYPE_2__ bna; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_nw_ioc_timeout (void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bnad_ioc_timeout(unsigned long data)
{
	struct bnad *bnad = (struct bnad *)data;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_ioc_timeout((void *) &bnad->bna.ioceth.ioc);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}