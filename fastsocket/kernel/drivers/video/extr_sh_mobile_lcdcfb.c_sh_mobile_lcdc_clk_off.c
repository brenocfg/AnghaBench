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
struct sh_mobile_lcdc_priv {int /*<<< orphan*/  dev; scalar_t__ dot_clk; int /*<<< orphan*/  hw_usecnt; } ;

/* Variables and functions */
 int atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_lcdc_clk_off(struct sh_mobile_lcdc_priv *priv)
{
	if (atomic_sub_return(1, &priv->hw_usecnt) == -1) {
		if (priv->dot_clk)
			clk_disable(priv->dot_clk);
		pm_runtime_put(priv->dev);
	}
}