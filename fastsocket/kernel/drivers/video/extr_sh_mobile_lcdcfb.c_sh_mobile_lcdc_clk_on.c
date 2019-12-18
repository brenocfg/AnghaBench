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
struct sh_mobile_lcdc_priv {scalar_t__ dot_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_usecnt; } ;

/* Variables and functions */
 scalar_t__ atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_lcdc_clk_on(struct sh_mobile_lcdc_priv *priv)
{
	if (atomic_inc_and_test(&priv->hw_usecnt)) {
		pm_runtime_get_sync(priv->dev);
		if (priv->dot_clk)
			clk_enable(priv->dot_clk);
	}
}