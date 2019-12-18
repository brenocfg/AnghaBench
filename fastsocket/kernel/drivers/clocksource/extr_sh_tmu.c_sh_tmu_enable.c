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
struct sh_tmu_priv {int rate; int /*<<< orphan*/  clk; TYPE_2__* pdev; } ;
struct sh_timer_config {int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {struct sh_timer_config* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCNT ; 
 int /*<<< orphan*/  TCOR ; 
 int /*<<< orphan*/  TCR ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_start_stop_ch (struct sh_tmu_priv*,int) ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sh_tmu_enable(struct sh_tmu_priv *p)
{
	struct sh_timer_config *cfg = p->pdev->dev.platform_data;
	int ret;

	/* enable clock */
	ret = clk_enable(p->clk);
	if (ret) {
		pr_err("sh_tmu: cannot enable clock \"%s\"\n", cfg->clk);
		return ret;
	}

	/* make sure channel is disabled */
	sh_tmu_start_stop_ch(p, 0);

	/* maximum timeout */
	sh_tmu_write(p, TCOR, 0xffffffff);
	sh_tmu_write(p, TCNT, 0xffffffff);

	/* configure channel to parent clock / 4, irq off */
	p->rate = clk_get_rate(p->clk) / 4;
	sh_tmu_write(p, TCR, 0x0000);

	/* enable channel */
	sh_tmu_start_stop_ch(p, 1);

	return 0;
}