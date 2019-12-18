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
struct omap_mbox {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  omap_mbox_irq_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_irq ) (struct omap_mbox*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct omap_mbox*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void enable_mbox_irq(struct omap_mbox *mbox, omap_mbox_irq_t irq)
{
	mbox->ops->enable_irq(mbox, irq);
}