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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct musb {int /*<<< orphan*/  lock; int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 struct musb* dev_to_musb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  musb_generic_disable (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_disable (struct musb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void musb_shutdown(struct platform_device *pdev)
{
	struct musb	*musb = dev_to_musb(&pdev->dev);
	unsigned long	flags;

	spin_lock_irqsave(&musb->lock, flags);
	musb_platform_disable(musb);
	musb_generic_disable(musb);
	if (musb->clock) {
		clk_put(musb->clock);
		musb->clock = NULL;
	}
	spin_unlock_irqrestore(&musb->lock, flags);

	/* FIXME power down */
}