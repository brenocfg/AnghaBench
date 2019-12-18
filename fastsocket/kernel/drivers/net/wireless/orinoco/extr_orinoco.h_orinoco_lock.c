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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct orinoco_private {int /*<<< orphan*/  lock; TYPE_2__ hw; int /*<<< orphan*/  ndev; scalar_t__ hw_unavailable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unlock_irqrestore ) (int /*<<< orphan*/ *,unsigned long*) ;int /*<<< orphan*/  (* lock_irqsave ) (int /*<<< orphan*/ *,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static inline int orinoco_lock(struct orinoco_private *priv,
			       unsigned long *flags)
{
	priv->hw.ops->lock_irqsave(&priv->lock, flags);
	if (priv->hw_unavailable) {
		DEBUG(1, "orinoco_lock() called with hw_unavailable (dev=%p)\n",
		       priv->ndev);
		priv->hw.ops->unlock_irqrestore(&priv->lock, flags);
		return -EBUSY;
	}
	return 0;
}