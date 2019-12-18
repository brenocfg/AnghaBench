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
struct sh_timer_config {int /*<<< orphan*/  clk; } ;
struct sh_cmt_priv {int width; int /*<<< orphan*/  clk; TYPE_2__* pdev; } ;
struct TYPE_3__ {struct sh_timer_config* platform_data; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMCNT ; 
 int /*<<< orphan*/  CMCOR ; 
 int /*<<< orphan*/  CMCSR ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_cmt_start_stop_ch (struct sh_cmt_priv*,int) ; 
 int /*<<< orphan*/  sh_cmt_write (struct sh_cmt_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sh_cmt_enable(struct sh_cmt_priv *p, unsigned long *rate)
{
	struct sh_timer_config *cfg = p->pdev->dev.platform_data;
	int ret;

	/* enable clock */
	ret = clk_enable(p->clk);
	if (ret) {
		pr_err("sh_cmt: cannot enable clock \"%s\"\n", cfg->clk);
		return ret;
	}

	/* make sure channel is disabled */
	sh_cmt_start_stop_ch(p, 0);

	/* configure channel, periodic mode and maximum timeout */
	if (p->width == 16) {
		*rate = clk_get_rate(p->clk) / 512;
		sh_cmt_write(p, CMCSR, 0x43);
	} else {
		*rate = clk_get_rate(p->clk) / 8;
		sh_cmt_write(p, CMCSR, 0x01a4);
	}

	sh_cmt_write(p, CMCOR, 0xffffffff);
	sh_cmt_write(p, CMCNT, 0);

	/* enable channel */
	sh_cmt_start_stop_ch(p, 1);
	return 0;
}