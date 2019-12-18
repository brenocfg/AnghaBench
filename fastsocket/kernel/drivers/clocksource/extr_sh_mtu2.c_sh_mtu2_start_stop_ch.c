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
struct sh_timer_config {int timer_bit; } ;
struct sh_mtu2_priv {TYPE_2__* pdev; } ;
struct TYPE_3__ {struct sh_timer_config* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSTR ; 
 int /*<<< orphan*/  sh_mtu2_lock ; 
 unsigned long sh_mtu2_read (struct sh_mtu2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mtu2_write (struct sh_mtu2_priv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sh_mtu2_start_stop_ch(struct sh_mtu2_priv *p, int start)
{
	struct sh_timer_config *cfg = p->pdev->dev.platform_data;
	unsigned long flags, value;

	/* start stop register shared by multiple timer channels */
	spin_lock_irqsave(&sh_mtu2_lock, flags);
	value = sh_mtu2_read(p, TSTR);

	if (start)
		value |= 1 << cfg->timer_bit;
	else
		value &= ~(1 << cfg->timer_bit);

	sh_mtu2_write(p, TSTR, value);
	spin_unlock_irqrestore(&sh_mtu2_lock, flags);
}