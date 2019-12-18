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
struct sh_mtu2_priv {int rate; int periodic; int /*<<< orphan*/  clk; TYPE_1__* pdev; } ;
struct TYPE_4__ {struct sh_timer_config* platform_data; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TCNT ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TGR ; 
 int /*<<< orphan*/  TIER ; 
 int /*<<< orphan*/  TIOR ; 
 int /*<<< orphan*/  TMDR ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mtu2_start_stop_ch (struct sh_mtu2_priv*,int) ; 
 int /*<<< orphan*/  sh_mtu2_write (struct sh_mtu2_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sh_mtu2_enable(struct sh_mtu2_priv *p)
{
	struct sh_timer_config *cfg = p->pdev->dev.platform_data;
	int ret;

	/* enable clock */
	ret = clk_enable(p->clk);
	if (ret) {
		pr_err("sh_mtu2: cannot enable clock \"%s\"\n", cfg->clk);
		return ret;
	}

	/* make sure channel is disabled */
	sh_mtu2_start_stop_ch(p, 0);

	p->rate = clk_get_rate(p->clk) / 64;
	p->periodic = (p->rate + HZ/2) / HZ;

	/* "Periodic Counter Operation" */
	sh_mtu2_write(p, TCR, 0x23); /* TGRA clear, divide clock by 64 */
	sh_mtu2_write(p, TIOR, 0);
	sh_mtu2_write(p, TGR, p->periodic);
	sh_mtu2_write(p, TCNT, 0);
	sh_mtu2_write(p, TMDR, 0);
	sh_mtu2_write(p, TIER, 0x01);

	/* enable channel */
	sh_mtu2_start_stop_ch(p, 1);

	return 0;
}