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
typedef  int /*<<< orphan*/  u8 ;
struct tc6393xb {int /*<<< orphan*/  lock; scalar_t__ scr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ SCR_FER ; 
 int /*<<< orphan*/  SCR_FER_SLCDEN ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct tc6393xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

int tc6393xb_lcd_set_power(struct platform_device *fb, bool on)
{
	struct platform_device *dev = to_platform_device(fb->dev.parent);
	struct tc6393xb *tc6393xb = platform_get_drvdata(dev);
	u8 fer;
	unsigned long flags;

	spin_lock_irqsave(&tc6393xb->lock, flags);

	fer = ioread8(tc6393xb->scr + SCR_FER);
	if (on)
		fer |= SCR_FER_SLCDEN;
	else
		fer &= ~SCR_FER_SLCDEN;
	iowrite8(fer, tc6393xb->scr + SCR_FER);

	spin_unlock_irqrestore(&tc6393xb->lock, flags);

	return 0;
}